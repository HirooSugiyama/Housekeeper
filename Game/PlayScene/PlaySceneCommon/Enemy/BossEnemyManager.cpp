/*
敵管理クラス
*/

#include<pch.h>

#include "BossEnemyManager.h"


//前方宣言
#include"../../Effect/Effect.h"

//当たり判定
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Protecter.h"
#include"../Administrator/Administrator.h"

//当たり判定の際に関数を使用
#include"../Administrator/Score.h"
#include"../ObjectModel/BoxModel.h"
#include"../Weapon/WeaponHand.h"
#include"../ObjectModel/SphereModel.h"
#include"../../PlaySceneDefence/DangerousLine.h"

//列挙型の使用
#include"../Player/ActionStateAttackEnemy.h"

//エフェクトの取得
#include"../../Effect/EffectManager.h"

#include"../Bullet/BulletManager.h"


//初期サイズ
const int BossEnemyManager::ENEMY_INIT_SIZE = 100;

//未使用の敵の出現座標
const DirectX::SimpleMath::Vector3 BossEnemyManager::NOT_SET_ENEMY_POSITION(-10.f, -10.f, -10.f);


//初期拡大率
const DirectX::SimpleMath::Vector3 BossEnemyManager::ENEMY_INIT_SCALE(1.f, 1.f, 1.f);

//敵の攻撃力
const int BossEnemyManager::ENEMY_ATTACK_NUM = 1;


//スコア値
const int BossEnemyManager::ENEMY_SCORE = 100;

//エフェクトの出現させる座標
const DirectX::SimpleMath::Vector3 BossEnemyManager::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);

//敵のプレイヤー捕捉範囲
const float BossEnemyManager::ENEMY_CAPTURE_RANGE = 5.f;

//反転数
const int BossEnemyManager::REVERSE_NUM = 2;

//BOSS生成時の通常敵数増加量
const int BossEnemyManager::ENEMY_ADDITIONAL_CAPACITY = 20;

//配下敵生成範囲
const int BossEnemyManager::SUBORDINATE_ENEMY_CREATE_RANGE = 70;


//ボス敵の配下敵生成数
const int BossEnemyManager::SUBORDINATE_ENEMY_CREATE_NUM = 5;

//ボス敵の通常敵生成数
const int BossEnemyManager::NORNAML_ENEMY_CREATE_NUM = 1;


//配下敵の生存数
const int BossEnemyManager::SUBORDINATE_ENEMY_ARIVE_NUM = 3;


//ボス敵の通常敵生成時のフェーズ番号
const int BossEnemyManager::NORMAL_ENEMY_CREATE_PHASE = 1;

/*===================================
コンストラクタ
===================================*/
BossEnemyManager::BossEnemyManager()
	:
	mpBossEnemy(),
	mEnemyAppearanceInterval(0),
	mpEnemyCall(nullptr),
	mpAdministrator(nullptr),
	mMaxEnemySpawnPositionZ(0),
	mLoadEnemyFileName("none"),
	mNowPhaseNum(0),
	mMaxPhaseNum(0),
	mNowEnemyBreakNum(),
	mBossEnemyUseFlag(false)
{
	//呼び出しクラスを定義
	mpEnemyCall = std::make_unique<EnemyCall>();

	mpBossEnemy = std::make_unique<BossEnemy>();
}

/*=================================
デストラクタ
===================================*/
BossEnemyManager::~BossEnemyManager()
{
}
/*=========================================================
初期化処理
引数：カメラへのアドレス、管理者クラスのアドレス
=========================================================*/
void BossEnemyManager::Initialize(CameraBase* camera, Administrator* pAdministrator, Player* pPlayer)
{
	//敵の読み込み
	this->LoadFile(mLoadEnemyFileName);

	//アドレス保存
	mpAdministrator = pAdministrator;

	//座標のアドレス保存
	mpBossEnemy->GetStateMove()->SetSavePlayerPointer(pPlayer->GetPlayerPositionAddress());

	//カメラのアドレスの保存
	mpBossEnemy->SaveCameraPointer(camera);
}

/*===================================
更新処理
===================================*/
void BossEnemyManager::Update()
{


	if (mBossEnemyUseFlag)
	{
		//ボス敵の更新処理
		if (mpBossEnemy->GetMovePhaseNumber() == mNowPhaseNum &&
			mpBossEnemy->GetState() == BossEnemyMainState::CREATE_BEFORE)
		{
			//出現状態へ
			mpBossEnemy->GetStateCreateBefore()->ChangeState();
		}
		//ボス敵の更新処理
		mpBossEnemy->Update();
	}
}

/*=================================
描画処理
===================================*/
void BossEnemyManager::Draw()
{
	if (mBossEnemyUseFlag)
	{
		//ボス敵の描画処理
		mpBossEnemy->Draw();
	}
}

/*=================================
終了処理
===================================*/
void BossEnemyManager::Finalize()
{
	mpBossEnemy->Finalize();
}

/*=======================================================================================================
敵の回数分だけ当たり判定を回す処理(ボス敵)
引数：弾管理クラスのアドレス
========================================================================================================*/
void BossEnemyManager::RoolBulletManagerChackhitBossEnemy(BulletManager* pBulletManager)
{
	//ボスを使用していないときは処理を通さない
	if (!mpBossEnemy->GetUseFlag())return;

	//撃破した数だけ増加させる
	int breaknum = pBulletManager->ChackHitBulletBossEnemy(mpBossEnemy.get());

	//撃破した数だけ増加させる
	mNowEnemyBreakNum += breaknum;

	//スコア増加
	mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE * breaknum);

}

/*=================================
読み込むファイル名を作成
引数：ステージ番号
返り値：ファイル名
===================================*/
std::string BossEnemyManager::CreateLoadEnemyFileName(std::string const& stagenum)
{
	std::string filetop = "Resources/CSV/Enemy",
		filebottom = ".csv",
		filename = "none";

	filename = filetop + stagenum + filebottom;

	return filename;

}


/*==========================================
全ての敵が死亡したことを確認するフラグ
==========================================*/
bool BossEnemyManager::AllEnemyDeathFlag()
{
	//現在のフェーズが最大フェーズ出ないならば処理を通さない
	if (mNowPhaseNum != mMaxPhaseNum)
	{
		return false;
	}
	if (mBossEnemyUseFlag)
	{
		if (mpBossEnemy->GetUseFlag())
		{
			return false;
		}
	}

	//ここに来る==全ての敵が未使用状態の場合
	return true;
}

/*==================================
生きている敵を一斉に爆破させる
===================================*/
void BossEnemyManager::ExplosionSimultaneousEnemy()
{
	if (mpBossEnemy->GetUseFlag())
	{
		//エフェクトを設定する
		this->SetEnemyEffect(eEffectType::BOMB, mpBossEnemy->GetEnemyModel()->GetPosition());
		mpBossEnemy->SelfDestroy();
	}
}

/*==================================================
ブロックとボス敵の衝突判定
引数：ブロックのアドレス
====================================================*/
void BossEnemyManager::ChackHitBlocklBossEnemy(Block* pBlock)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//衝突判定
	if (pC.Intersect(pBlock->GetBoxModel()->GetAABBCollider(),
		mpBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//ブロックを破壊する
		pBlock->SelfDestroy();

		//エフェクトの設定
		this->SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
	}
}

/*==================================================
プレイヤーとボス敵の衝突判定
引数：プレイヤーのアドレス
====================================================*/
void BossEnemyManager::ChackHitPlayerBossEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//プレイヤーがダメージ状態なら処理をしない
	if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) return;

	//衝突判定
	if (pC.Intersect(pPlayer->GetPlayerCollider(),
		mpBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//プレイヤーにダメージを与える
		pPlayer->ChangeStateDamage();
	}
}

/*==================================================
弱攻撃状態のプレイヤーとボス敵の衝突判定
引数：プレイヤーのアドレス
====================================================*/
void BossEnemyManager::ChackHitNormalAttackPlayerBossEnemy(Player* pPlayer)
{
	Collider& pC = Collider::GetColliderInstance();

	//選択肢にnullが入る可能性があるためチェックする
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return;
	//もしプレイヤーが弱攻撃状態でないならば通らない
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return;

	//回避状態の場合も攻撃を受けない
	if (mpBossEnemy->GetStateMove()->GetMoveState() == BossEnemyMoveState::ESCAPE)return;

	//当たっていたら処理をする
	if (pC.Intersect(
		pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
		mpBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//弱攻撃のダメージを与える
		int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

		bool breakjuge = mpBossEnemy->Damage(damageNum, mpBossEnemy->GetEnemyHP());

		//もし敵を倒していたら
		if (breakjuge)
		{
			//撃破数追加
			mNowEnemyBreakNum++;

			//スコアを増やして
			mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE);
		}

		//逃走状態とする
		mpBossEnemy->GetStateMove()->ChangeStateEscape();

		//エフェクトを設定する
		this->SetEnemyEffect(eEffectType::SLASH, mpBossEnemy->GetEnemyModel()->GetPosition());

	}
}

/*==================================================
柵とボス敵の衝突判定
引数：柵の衝突判定アドレス
====================================================*/
void BossEnemyManager::ChackHitWallBossEnemy(AABB* pWallCollider)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();
	
	//当たっていたら処理をする
	if (pC.Intersect(
		mpBossEnemy->GetEnemyModel()->GetAABBCollider(),	//敵の当たり判定
		pWallCollider))										//地上オブジェクトの当たり判定
	{
		//Todo:停止させる
		DirectX::SimpleMath::Vector3 shiftPosition = mpBossEnemy->GetEnemyModel()->GetPosition();
		shiftPosition.x = pWallCollider->mMin.x;
		mpBossEnemy->GetEnemyModel()->SetPosition(shiftPosition);
	}
}

/*===================================
ボス範囲とプレイヤーの衝突判定
引数：プレイヤーのアドレス
===================================*/
void BossEnemyManager::ChackHitPlayerBossEnemyArea(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//移動状態以外なら処理をしない
	if (mpBossEnemy->GetState() != BossEnemyMainState::MOVE)return;

	//衝突判定
	if (pC.Intersect(
		mpBossEnemy->GetPlayerRecognitionRangeCollider(),
		pPlayer->GetPlayerCollider()))
	{

		//配下敵生成処理へ
		mpBossEnemy->ChangeStateCreate();

		//生成フラグが立っていなかったら建てる
		if (!mpBossEnemy->GetActiveFlag())
		{
			mpBossEnemy->SetActiveFlag(true);
		}
	}
}

/*===================================
ファイルから情報を取得する:private
引数：ファイルパス、カメラへのアドレス
===================================*/
void BossEnemyManager::LoadFile(std::string filepath)
{
	//初期化
	DirectX::SimpleMath::Vector3 pos= NOT_SET_ENEMY_POSITION;
	int phasenum = 0;


	//情報読み込み
	mpEnemyCall->LoadInfo(filepath);

	//BOSS生成処理
	mBossEnemyUseFlag = this->CreateBoss();

	//不要になったので削除
	mpEnemyCall->Reset();
}

/*======================================================================
ボス敵生成処理
========================================================================*/
bool BossEnemyManager::CreateBoss()
{
	if (mpEnemyCall->GetBossEnemyStructer().mPhaseNumber == 0)return false;

	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 pos = NOT_SET_ENEMY_POSITION;
	int phasenum = 0;

	//BOSS生成
	pos = mpEnemyCall->GetBossEnemyStructer().mVectorESPosition;
	phasenum = mpEnemyCall->GetBossEnemyStructer().mPhaseNumber;
	mpBossEnemy->SetMovePhaseNumber(phasenum);
	mpBossEnemy->Initialize(pos);

	return true;
}


/*======================================================================
エフェクトを設定する:private
引数：エフェクトの種類、敵の座標、
		敵の要素番号、エフェクトフラグを建てるか(true：建てる)
========================================================================*/
void BossEnemyManager::SetEnemyEffect(eEffectType const& type, DirectX::SimpleMath::Vector3 const& pos)
{
	//エフェクトマネージャーの取得
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(pos + EFFECT_SHIFT_POSITION);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
}

/*==================================================
座標生成:private
引数：基準となる座標
返り値：生成座標
===================================================*/
DirectX::SimpleMath::Vector3 BossEnemyManager::CreatePosition(DirectX::SimpleMath::Vector3 const& position)
{
	//int型に戻すため一時的に10倍する
	DirectX::SimpleMath::Vector3 castPosition = position * 10.f;

	// 非決定的な乱数生成器でシード生成機を生成
	std::random_device rnd;
	//メルセンヌツイスターの32ビット版、引数は初期シード
	std::mt19937 mt(rnd());
	//乱数を振る
	std::uniform_int_distribution<> randX
	(
		castPosition.x - SUBORDINATE_ENEMY_CREATE_RANGE,
		castPosition.x + SUBORDINATE_ENEMY_CREATE_RANGE
	);

	std::uniform_int_distribution<> randZ
	(
		castPosition.z - SUBORDINATE_ENEMY_CREATE_RANGE,
		castPosition.z + SUBORDINATE_ENEMY_CREATE_RANGE
	);

	//座標設定
	castPosition.x = randX(mt);
	castPosition.z = randZ(mt);

	//float変換(/10)
	castPosition /= 10.f;
	castPosition.y = position.y;

	//ステージ端の処理
	if (castPosition.x > Utility::FIELD_MAX_SIZE_X)
	{
		castPosition.x = Utility::FIELD_MAX_SIZE_X;
	}
	else if (castPosition.x < Utility::FIELD_MIN_SIZE_X)
	{
		castPosition.x = Utility::FIELD_MIN_SIZE_X;
	}

	if (castPosition.z > Utility::FIELD_MAX_SIZE_Z)
	{
		castPosition.z = Utility::FIELD_MAX_SIZE_Z;
	}
	else if (castPosition.z < Utility::FIELD_MIN_SIZE_Z)
	{
		castPosition.z = Utility::FIELD_MIN_SIZE_Z;
	}

	return castPosition;
}
