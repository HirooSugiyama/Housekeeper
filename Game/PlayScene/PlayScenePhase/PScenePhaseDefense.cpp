/*
防衛フェーズ
作成者：杉山
作成日：2021/06/16
*/

#include"pch.h"
#include "PScenePhaseDefense.h"

//所持元
#include"../PlayScene.h"



//情報共有で使用
#include"Game/Component/SceneComponent/PtoRSceneComponent.h"

//エフェクトの描画で使用
#include"../Effect/EffectManager.h"

//関数の使用
#include"../PlaySceneCommon/Player/Player.h"
#include "../PlaySceneCommon/Player/PlayerActionState.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/Player/ActionStateBase.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/Score.h"
#include"../PlaySceneCommon/Block/BlockManager.h"
#include"../PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"../PlaySceneCommon/Wall/WallManager.h"
#include"../PlaySceneCommon/GridLine/GridLineManager.h"
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneCommon/Player/ActionStateAttackEnemy.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"
#include"../PlayScenePhase/PScenePhaseEndAnimation.h"
#include"../PlaySceneCommon/Player/ActionStateDefenseHouse.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"
#include"../../UI/UI.h"

#include"Libraries/MyLibraries/CameraBase.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"





//カメラ座標
const DirectX::SimpleMath::Vector3 PScenePhaseDefense::PIXED_CAMERA_POSITION(0.0f, 55.0f, 1.0f);

/*=====================
コンストラクタ
引数：なし
=====================*/
PScenePhaseDefense::PScenePhaseDefense()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mpDangerousLine(nullptr),
	mpSampleBlock(nullptr),
	mpDetectNormalEnemy(nullptr),
	mpDetectSubordinateEnemy(nullptr),
	mpDetectBossEnemy(nullptr),
	mRedAssertFlag(false),
	mPhaseCount(1),
	mAllPhaseNum(0),
	mShopOpenFlag(false),
	mDefenseState(eDefenseState::MOVE),
	mMoveCameraSavePosition(DirectX::SimpleMath::Vector3::Zero),
	mWipeFlag(false)
{
	mpDangerousLine = std::make_unique<DangerousLine>();
	mpSampleBlock = std::make_unique<PreparingBlock>();
	mpDetectNormalEnemy = std::make_unique<DetectNormalEnemy>();
	mpDetectSubordinateEnemy = std::make_unique<DetectSubordinateEnemy>();
	mpDetectBossEnemy = std::make_unique<DetectBossEnemy>();
}

/*=====================
デストラクタ
=====================*/
PScenePhaseDefense::~PScenePhaseDefense()
{
}

/*=============================
初期化処理
引数：所有先のポインタ
返り値：なし
===============================*/
void PScenePhaseDefense::Initialize(PlayScene* pPlayScene)
{
	//ポインタの保存
	mpPlayScene = pPlayScene;

	//警告ラインの初期化処理
	mpDangerousLine->Initialize();
	//見本ブロックの初期化処理
	mpSampleBlock->Initialize();

	//ポインタの都合上こちらで初期化
	PlayScenePhaseBase::GetPlayer()->Initialize
	(
		PlayScenePhaseBase::GetBlockManager(),
		PlayScenePhaseBase::GetAdministrator(),
		mpSampleBlock.get(),
		PlayScenePhaseBase::GetUI()
	);

	//ポインタの保存
	PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->
		SetWeaponManagerPointer(PlayScenePhaseBase::GetWeaponManager());

	PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->
		SetBulletManagerPointer(PlayScenePhaseBase::GetBulletManager());

	mAllPhaseNum = mpPlayScene->GetMaxPhaseNum();

	//管理者クラスのポインタを保存する
	mpDetectNormalEnemy->SetAdministrator(PlayScenePhaseBase::GetAdministrator());
	mpDetectSubordinateEnemy->SetAdministrator(PlayScenePhaseBase::GetAdministrator());
	mpDetectBossEnemy->SetAdministrator(PlayScenePhaseBase::GetAdministrator());
}

/*=====================
更新処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseDefense::Update()
{
	//カメラ情報を保存
	auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();

	//敵衝突判定の配列初期化処理
	/*通常敵*/
	mpDetectNormalEnemy->ResetChackColliderEnemy();
	mpDetectNormalEnemy->SetChackColliderEnemy(PlayScenePhaseBase::GetEnemyManager()->GetUseNormalEnemyVector());

	//ボス敵使用フラグ
	if (PlayScenePhaseBase::GetEnemyManager()->GetBossEnemyUseFlag())
	{
		/*配下敵*/
		mpDetectSubordinateEnemy->ResetChackColliderEnemy();
		mpDetectSubordinateEnemy->SetChackColliderEnemy(PlayScenePhaseBase::GetEnemyManager()->GetUseSubordinateEnemyVector());
		/*ボス敵*/
		mpDetectBossEnemy->ResetChackColliderEnemy();
		mpDetectBossEnemy->SetChackColliderEnemy(PlayScenePhaseBase::GetEnemyManager()->GetBossEnemyVector());
	}




	//オブジェクトの更新処理
	this->ObjectUpdate();

	//赤色点滅エフェクトをつけるかどうか
	this->RedAssertSet();

	//カメラ切り替え処理
	this->ChangeCamera();

	//パドルの情報を摘出
	DirectX::SimpleMath::Vector3 playerpos
		= PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();

	//カメラの更新
	mpPlayScene->GetCameraPointer()->Update(playerpos);

	//フェーズ更新処理
	this->PhaseToUpdate();

	//カメラの位置を保存する
	DirectX::SimpleMath::Vector3 cameraPosition(DirectX::SimpleMath::Vector3::Zero);
	cameraPosition = mpPlayScene->GetCameraPointer()->GetEyePosition();
	pCiIF.SetCameraPosition(cameraPosition);


	//プレイヤーの攻撃判定処理
	//攻撃していなかったら通さない
	if (PlayScenePhaseBase::GetPlayer()->GetActionState() == ePlayerActionState::ATTACK_ENEMY)
	{
		//攻撃判定処理
		int breakNum{ 0 };
		breakNum += mpDetectNormalEnemy->ChackHitNormalAttackPlayerEnemy(PlayScenePhaseBase::GetPlayer());
		breakNum += static_cast<int>(mpDetectBossEnemy->ChackHitNormalAttackPlayerBossEnemy(PlayScenePhaseBase::GetPlayer()));

		//配下敵は撃破数を加算しない
		mpDetectSubordinateEnemy->ChackHitNormalAttackPlayerSubordinateEnemy(PlayScenePhaseBase::GetPlayer());

		//撃破数があれば
		if (breakNum != 0)
		{
			//撃破数を追加
			PlayScenePhaseBase::GetEnemyManager()->AddBreakEnemyNum(breakNum);
		}	
	}	

	//当たり判定の処理
	this->ColliderUpdate();

}

/*============================
State変更前のリセット処理
引数：なし
返り値：なし
=============================*/
void PScenePhaseDefense::Reset()
{
	//敵管理クラスのフェーズを更新する
	PlayScenePhaseBase::GetEnemyManager()->SetNowPhaseNum(mPhaseCount);
	//天球を変える
	PlayScenePhaseBase::GetAdministrator()->DirectAcceserCelestialSphere()->
		ChangeSphereModelNight();

	//カメラを変更
	mpPlayScene->ChangeMainCamera();

	//カメラ行列を取得
	CameraInfoComponent& pPVIf = CameraInfoComponent::GetCameraInfoComponentInstance();

	//定点カメラに変更する
	pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
	pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
}

/*==============================
描画処理
引数：なし
返り値：なし
================================*/
void PScenePhaseDefense::Draw()
{
	//エフェクトの描画処理
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();

	//オブジェクトの描画処理
	this->ObjectDraw();

	/*ここより下にEffectの処理を書かないと表示されない！(描画順の関係)*/
	//UIの描画処理
	PlayScenePhaseBase::GetUI()->Draw();
	//プレイヤーの状態の描画
	PlayScenePhaseBase::GetPlayer()->GetActionStateBase()->Draw();


	
}

/*====================================
オブジェクトの更新処理:private
引数：なし
返り値：なし
====================================*/
void PScenePhaseDefense::ObjectUpdate()
{
	//プレイヤーの更新処理
	PlayScenePhaseBase::GetPlayer()->Update();

	//ブロックの更新処理
	PlayScenePhaseBase::GetBlockManager()->Update();

	//敵の更新処理
	PlayScenePhaseBase::GetEnemyManager()->Update();

	//弾管理クラスの初期化処理
	PlayScenePhaseBase::GetBulletManager()->Update();

	//もしプレイヤーがダメージを受けていたら処理を通さない
	//攻撃しているときも処理を通さない
	if (PlayScenePhaseBase::GetPlayer()->GetPlayerState() != ePlayerState::DAMAGE &&
		PlayScenePhaseBase::GetPlayer()->GetActionState() != ePlayerActionState::ATTACK_ENEMY) 
	{
		//見本ブロックの更新処理
		mpSampleBlock->Update
		(
			PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition(),
			PlayScenePhaseBase::GetGridLineManager()
		);
	}

	//管理者の更新処理
	PlayScenePhaseBase::GetAdministrator()->Update();

	//UIに情報を渡す
	int scoreNum = PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum();
	int nowNum = PlayScenePhaseBase::GetEnemyManager()->GetBreakEnemyNum();
	int maxNum = PlayScenePhaseBase::GetEnemyManager()->GetMaxEnemyNum();

	PlayScenePhaseBase::GetUI()->SetAllEnemyNum(maxNum);
	PlayScenePhaseBase::GetUI()->SetRemainingEnemyNum(nowNum);
	PlayScenePhaseBase::GetUI()->SetScoreNum(scoreNum);


}
/*====================================
当たり判定の処理:private
引数：なし
返り値：なし
====================================*/
void PScenePhaseDefense::ColliderUpdate()
{
	//簡略化変数の宣言
	Player* pPlayer = PlayScenePhaseBase::GetPlayer();
	Protecter* pProtecter = PlayScenePhaseBase::GetProtecter();
	BlockManager* pBlockManager = PlayScenePhaseBase::GetBlockManager();
	BulletManager* pBulletManager = PlayScenePhaseBase::GetBulletManager();

	//敵撃破数カウント
	int breakNum{ 0 };

	/*通常敵*/
	//プレイヤーと敵の当たり判定計測
	mpDetectNormalEnemy->ChackHitPlayerEnemy(pPlayer);
	//拠点と敵の当たり判定計測
	mpDetectNormalEnemy->ChackHitProtecterEnemy(pProtecter);
	//ブロックと敵の当たり判定
	pBlockManager->RoolNormalEnemyChackHit(mpDetectNormalEnemy.get());
	//地上オブジェクトと敵の当たり判定
	PlayScenePhaseBase::GetGroundObjectManager()->RoolNormalEnemyChackHit(mpDetectNormalEnemy.get());
	//柵と敵の当たり判定を回す
	PlayScenePhaseBase::GetWallManager()->RoolNormalEnemyChackHit(mpDetectNormalEnemy.get());
	//警告ラインと敵の当たり判定
	mRedAssertFlag = mpDetectNormalEnemy->ChackHitDangerousLineEnemy(mpDangerousLine.get());	
	//弾と敵の当たり判定
	breakNum += mpDetectNormalEnemy->RoolBulletManagerChackhit(pBulletManager);
	//プレイヤーと敵の距離判定
	mpDetectNormalEnemy->ChackDistanceTargetEnemy(pPlayer->GetPlayerModel()->GetPosition());

	//ボス敵使用フラグ
	if (PlayScenePhaseBase::GetEnemyManager()->GetBossEnemyUseFlag())
	{
		/*ボス敵*/
		//プレイヤーとボス敵の当たり判定
		mpDetectBossEnemy->ChackHitPlayerBossEnemy(pPlayer);
		//地上オブジェクトと敵の当たり判定
		pBlockManager->RoolBossEnemyChackHit(mpDetectBossEnemy.get());
		//地上オブジェクトと敵の当たり判定
		pBlockManager->RoolSubordinateEnemyChackHit(mpDetectSubordinateEnemy.get());
		//弾と敵の当たり判定
		breakNum += static_cast<int>(mpDetectBossEnemy->RoolBulletManagerChackhitBossEnemy(pBulletManager));
		//ボス範囲とプレイヤーの衝突判定
		mpDetectBossEnemy->ChackHitPlayerBossEnemyArea(pPlayer);

		/*配下敵*/
		//プレイヤーと配下敵の当たり判定
		mpDetectSubordinateEnemy->ChackHitPlayerSubordinateEnemy(pPlayer);
		//弾と敵の当たり判定
		mpDetectSubordinateEnemy->RoolBulletManagerChackhitSubordinateEnemy(pBulletManager);
	}

	// ブロックと見本ブロックの当たり判定～ブロックの重なりを防ぐ～
	pBlockManager->ChackHitSampleBlockBlock(mpSampleBlock.get(), pPlayer);
	//ブロックとプレイヤーの当たり判定
	pBlockManager ->ChackhitPlayerBlock(pPlayer);
	//判定用ラインと見本ブロックの当たり判定
	PlayScenePhaseBase::GetGridLineManager()->ChackHitPreparingBlockGridLine(pPlayer, mpSampleBlock.get());
	//プレイヤーと地上オブジェクトの当たり判定
	PlayScenePhaseBase::GetGroundObjectManager()->ChackHitPlayerGroundObject(pPlayer);
	//ブロックと弾の衝突判定
	pBulletManager->RoolChackHitBlock(pBlockManager);
	//弾とプレイヤーの衝突判定
	pBulletManager->ChackHitBulletPlayer(pPlayer);



	//撃破数があれば
	if (breakNum != 0)
	{
		//撃破数を追加
		PlayScenePhaseBase::GetEnemyManager()->AddBreakEnemyNum(breakNum);
	}






}

/*====================================
オブジェクトの描画処理:private
引数：なし
返り値：なし
====================================*/
void PScenePhaseDefense::ObjectDraw()
{
	//警告ラインの描画処理
	mpDangerousLine->Draw();
}

/*===========================================
赤色点滅エフェクトをつけるかどうか:private
引数：なし
返り値：なし
===========================================*/
void PScenePhaseDefense::RedAssertSet()
{
	//もしフラグが立っていたら
	if (mRedAssertFlag)
	{
		PlayScenePhaseBase::GetUI()->RedAssertControl(true);
	}
	//立っていなかったら
	else
	{
		PlayScenePhaseBase::GetUI()->RedAssertControl(false);
	}

}

/*===========================================
フェーズ更新処理:private
引数：なし
返り値：なし
===========================================*/
void PScenePhaseDefense::PhaseToUpdate()
{
	//簡略化変数の宣言
	int nowtime = PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->GetMainTimer();
	int maxtime = PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->GetMaxTime();
	
	if (nowtime == maxtime)
	{
		//フェーズカウントが最大になったら
		if (mPhaseCount == mAllPhaseNum) 
		{
			//スコアの取得
 			PtoRSceneComponent& pPR = PtoRSceneComponent::GetPtoRIFInstance();
			pPR.SetScoreNum(PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum());
			mpPlayScene->GetEndAnimation()->SetUseAnim(eUseEndAnim::WIN_TIME);
			mpPlayScene->ChangePhaseToEndAnimation();
			mpPlayScene->GetPhase()->Reset();
		}

		//周期カウントを更新
		mPhaseCount++;
		//敵管理クラスのフェーズを更新する
		PlayScenePhaseBase::GetEnemyManager()->SetNowPhaseNum(mPhaseCount);

		//サウンド再生
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_ENEMYSPAWN);

		//タイマーをリセットする
		PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->ResetMainTimer();
	}


	//ショップへの移行処理
	if (PlayScenePhaseBase::GetGroundObjectManager()->GetPlayerShopTouchFlag()&&
		mShopOpenFlag == false)
	{


		//状態移行処理を行う
		mpPlayScene->ChangePhaseToWeaponShop();
		mpPlayScene->GetPhase()->Reset();

		//フラグを付ける
		mShopOpenFlag = true;
	}
	else if (!PlayScenePhaseBase::GetGroundObjectManager()->GetPlayerShopTouchFlag()&&
		mShopOpenFlag == true)
	{
		//フラグを降ろす
		mShopOpenFlag = false;
	}


	
}

/*===========================================
カメラ視点変更処理:private
引数：なし
返り値：なし
===========================================*/
void PScenePhaseDefense::ChangeCamera()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (!pKey->ChangeCamera()|| !pGamePad->ChangeCamera())
	{
		return;
	}

	switch (mDefenseState)
	{
		//移動状態だった場合
		case eDefenseState::MOVE:
		{
			mDefenseState = eDefenseState::PIXED;
			mMoveCameraSavePosition = mpPlayScene->GetCameraPointer()->GetEyePosition();

			//定点カメラに変更する
			mpPlayScene->ChangeFixedCamera();
			mpPlayScene->GetCameraPointer()->SetEyePosition(PIXED_CAMERA_POSITION);			//座標指定
			mpPlayScene->GetCameraPointer()->CalculationMatrix();

			//カメラ行列を取得
			auto& pPVIf = CameraInfoComponent::GetCameraInfoComponentInstance();
			
			//定点カメラに変更する
			pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
			pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
			break;
		}
		//定点カメラだった場合
		case eDefenseState::PIXED:
		{
			mDefenseState = eDefenseState::MOVE;
			//定点カメラに変更する
			mpPlayScene->ChangeMainCamera();
			mpPlayScene->GetCameraPointer()->SetEyePosition(mMoveCameraSavePosition);			//座標指定
			//カメラ行列を取得
			auto& pPVIf = CameraInfoComponent::GetCameraInfoComponentInstance();
			
			//定点カメラに変更する
			pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
			pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());

			break;
		}
	}
}
