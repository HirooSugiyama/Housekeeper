/*
敵管理クラス
作成者：杉山
作成日：2021/10/21
*/

#include<pch.h>

#include "EnemyManager.h"


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
#include"../Bullet/BulletManager.h"

//列挙型の使用
#include"../Player/ActionStateAttackEnemy.h"

//エフェクトの取得
#include"../../Effect/EffectManager.h"
#include"EnemyCommonFunction.h"


//初期サイズ
const int EnemyManager::ENEMY_INIT_SIZE = 100;

//未使用の敵の出現座標
const DirectX::SimpleMath::Vector3 EnemyManager::NOT_SET_ENEMY_POSITION(-10.f, -10.f, -10.f);


//初期拡大率
const DirectX::SimpleMath::Vector3 EnemyManager::ENEMY_INIT_SCALE(1.f, 1.f, 1.f);


//BOSS生成時の通常敵数増加量
const int EnemyManager::ENEMY_ADDITIONAL_CAPACITY = 20;

//配下敵生成範囲
const int EnemyManager::SUBORDINATE_ENEMY_CREATE_RANGE = 70;


//ボス敵の配下敵生成数
const int EnemyManager::SUBORDINATE_ENEMY_CREATE_NUM = 5;

//ボス敵の通常敵生成数
const int EnemyManager::NORNAML_ENEMY_CREATE_NUM = 1;


//配下敵の生存数
const int EnemyManager::SUBORDINATE_ENEMY_ARIVE_NUM = 3;


//ボス敵の通常敵生成時のフェーズ番号
const int EnemyManager::NORMAL_ENEMY_CREATE_PHASE = 1;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyManager::EnemyManager()
	:
	mpEnemy{},
	mpBossEnemy(),
	mpSubordinateEnemy{},
	mpEnemyCall(nullptr),
	mpAdministrator(nullptr),
	mMaxEnemySpawnPositionZ(0),
	mLoadEnemyFileName("none"),
	mNowPhaseNum(0),
	mMaxPhaseNum(0),
	mNowEnemyBreakNum(),
	mBossEnemyUseFlag(false)
{
	//サイズをメモリ確保用最大数に設定する
	mpEnemy.resize(ENEMY_INIT_SIZE);

	//呼び出しクラスを定義
	mpEnemyCall = std::make_unique<EnemyCall>();


	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		mpEnemy[i] = std::make_unique<Enemy>();
	}
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		mpSubordinateEnemy[i] = std::make_unique<SubordinateEnemy>();
	}
	mpBossEnemy = std::make_unique<BossEnemy>();

}

/*=================================
デストラクタ
===================================*/
EnemyManager::~EnemyManager()
{
}
/*=========================================================
初期化処理
引数：カメラへのアドレス、管理者クラスのアドレス、プレイヤーのアドレス
返り値：なし
=========================================================*/
void EnemyManager::Initialize(CameraBase* camera, Administrator* pAdministrator, Player* pPlayer)
{
	//敵の読み込み
	this->LoadFile(mLoadEnemyFileName);

	//アドレス保存
	mpAdministrator = pAdministrator;

	//座標のアドレス保存
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mpEnemy[i]->GetStateMove()->SetChasePlayerPositon(pPlayer->GetPlayerPositionAddress());
	}
	mpBossEnemy->GetStateMove()->SetSavePlayerPointer(pPlayer->GetPlayerPositionAddress());
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		mpSubordinateEnemy[i]->GetStateMove()->GetWalk()->SetSavePlayerPointer(pPlayer->GetPlayerPositionAddress());
	}

	//カメラのアドレスの保存
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mpEnemy[i]->SaveCameraPointer(camera);
	}
	mpBossEnemy->SaveCameraPointer(camera);
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		mpSubordinateEnemy[i]->SaveCameraPointer(camera);
	}
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyManager::Update()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		//使用中のみ
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//指定されたフェーズ番号より小さい番号を持つの敵のみ処理を通す
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum) continue;

		//例外数字の場合も処理を通さない
		if (mpEnemy[i]->GetMovePhaseNumber() == Utility::EXCEPTION_NUM) continue;

		//もし待機状態の敵がいたら
		if (mpEnemy[i]->GetEnemyMainState() == EnemyMainState::CREATE_BEFORE)
		{
			//出現状態へ
			mpEnemy[i]->GetStateCreateBefore()->ChangeState();
		}

		//敵の更新処理
		mpEnemy[i]->Update();
	}

	//ボス敵使用中の処理
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

		//生成状態ならば、生成する
		if (mpBossEnemy->GetState() == BossEnemyMainState::CREATE&&
			this->ChackSubordinateEnemyUseNum() <= SUBORDINATE_ENEMY_ARIVE_NUM)
		{
			//生成する
			this->CreateSubordinateEnemy();
		}

		//配下敵の更新処理
		for (int j = 0; j < SUBORDINATE_ENEMY_NUM; j++)
		{
			//未使用時は処理をしない
			if (!mpSubordinateEnemy[j]->GetUseFlag())continue;

			//もしプレイヤーがダメージ状態になったら
			mpSubordinateEnemy[j]->Update();
		}
	}
}

/*=================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyManager::Draw()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		//未使用状態の敵は通さない
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//例外数字の場合も処理を通さない
		if (mpEnemy[i]->GetMovePhaseNumber() == Utility::EXCEPTION_NUM) continue;

		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() <= mNowPhaseNum)
		{
			mpEnemy[i]->Draw();
		}
	}
	if (mBossEnemyUseFlag)
	{
		//ボス敵の描画処理
		mpBossEnemy->Draw();

		//配下敵の描画処理
		for (int j = 0; j < SUBORDINATE_ENEMY_NUM; j++)
		{
			//未使用時は処理をしない
			if (!mpSubordinateEnemy[j]->GetUseFlag())continue;

			mpSubordinateEnemy[j]->Draw();
		}
	}
	
}

/*=================================
終了処理
引数：なし
返り値：なし
===================================*/
void EnemyManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		if (mpEnemy[i] != nullptr) 
		{
			mpEnemy[i]->Finalize();
		}	
	}
}

/*========================================
リセット処理(ポインタは保持)
引数：なし
返り値：なし
=========================================*/
void EnemyManager::Reset()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		if (mpEnemy[i] != nullptr)
		{
			mpEnemy[i]->SelfDestroy();
		}
	}
}

/*=================================
読み込むファイル名を作成
引数：ステージ番号
返り値：ファイル名
===================================*/
std::string EnemyManager::CreateLoadEnemyFileName(const std::string & stagenum)
{
	std::string filetop = "Resources/CSV/Enemy",
		filebottom = ".csv",
		filename = "none";

	filename = filetop + stagenum + filebottom;

	return filename;

}


/*==========================================
全ての敵が死亡したことを確認するフラグ
引数：なし
返り値：生存フラグ
==========================================*/
bool EnemyManager::AllEnemyDeathFlag()
{
	//現在のフェーズが最大フェーズ出ないならば処理を通さない
	if (mNowPhaseNum != mMaxPhaseNum)
	{
		return false;
	}

	//敵の数だけ行う
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用している敵がいたら
		if (mpEnemy[i]->GetUseFlag())
		{
			//falseを返す
			return false;
		}
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
引数：なし
返り値：なし
===================================*/
void EnemyManager::ExplosionSimultaneousEnemy()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//未使用状態の敵は通さない
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//削除処理
		mpEnemy[i]->SelfDestroy();

		//エフェクトの設定
		EnemyCommonFunction::SetEnemyEffect
		(
			eEffectType::BOMB,
			mpEnemy[i]->GetEnemyModel()->GetPosition()
		);
	}
	if (mBossEnemyUseFlag)
	{
		//エフェクトの設定
		EnemyCommonFunction::SetEnemyEffect
		(
			eEffectType::BOMB,
			mpBossEnemy->GetEnemyModel()->GetPosition()
		);

		//削除処理
		mpBossEnemy->SelfDestroy();

		//配下敵の描画処理
		for (int j = 0; j < SUBORDINATE_ENEMY_NUM; j++)
		{
			//未使用時は処理をしない
			if (!mpSubordinateEnemy[j]->GetUseFlag())continue;

			//エフェクトの設定
			EnemyCommonFunction::SetEnemyEffect
			(
				eEffectType::BOMB,
				mpSubordinateEnemy[j]->GetEnemyModel()->GetPosition()
			);

			//削除処理
			mpSubordinateEnemy[j]->SelfDestroy();
		}
	}
}

/*===================================
ブロック衝突フラグを下す
引数：なし
返り値：なし
===================================*/
void EnemyManager::ResetEnemyBlockHitFlag()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用中ではないなら通さない。
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//フェーズがまだ来てなければ処理を行わない
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum)continue;

		//敵の現在の状態が移動状態以外ならば
		if (mpEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//衝突フラグを下す
		if (mpEnemy[i]->GetStateMove()->GetBlockHitFlag() == EnemyMainStateMove::EnemyBlockHit::HIT)
		{
			mpEnemy[i]->GetStateMove()->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NOT_HIT);
		}	
	}
}

/*===================================
配下敵生成:private
引数：なし
返り値：なし
===================================*/
void EnemyManager::CreateSubordinateEnemy()
{
	//短縮用変数の宣言
	DirectX::SimpleMath::Vector3 position = NOT_SET_ENEMY_POSITION;
	
	//生成数
	int createNum{ 0 };
	
	//アドレス保存用変数
	std::vector<SubordinateEnemy*> pAddress;
	
	//配下敵の生成処理
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM && createNum < SUBORDINATE_ENEMY_CREATE_NUM; i++)
	{
		//使用中の敵は処理しない
		if (mpSubordinateEnemy[i]->GetUseFlag())continue;
		
		position = this->CreatePosition(mpBossEnemy->GetEnemyModel()->GetPosition());
		mpSubordinateEnemy[i]->Initialize(position);
		createNum++;
	
		//アドレス保存
		pAddress.push_back(mpSubordinateEnemy[i].get());
	}
	//ボス敵に保存する
	mpBossEnemy->SetSaveSubordinateEnemy(pAddress);
	
	createNum = 0;

	pAddress.clear();
	
	//通常敵の生成処理
	for (int i = 0; i < static_cast<int>(mpEnemy.size()) && createNum < NORNAML_ENEMY_CREATE_NUM; i++)
	{
		//使用中の敵は処理しない
		if (mpEnemy[i]->GetUseFlag())continue;
	
		position = this->CreatePosition(mpBossEnemy->GetEnemyModel()->GetPosition());
		mpEnemy[i]->Initialize(position);
		mpEnemy[i]->SetMovePhaseNumber(NORMAL_ENEMY_CREATE_PHASE);
		createNum++;
	}
}

/*===================================
使用中のポインタのアクセサ:private
引数：ファイルパス、カメラへのアドレス
返り値：各敵の可変長配列
===================================*/
std::vector<Enemy*> EnemyManager::GetUseNormalEnemyVector()
{
	std::vector<Enemy*> returnVector{};
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用中ではないなら通さない。
		if (!mpEnemy[i]->GetUseFlag()) continue;
		
		//フェーズがまだ来てなければ処理を行わない
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum)continue;

		returnVector.push_back(mpEnemy[i].get());
	}

	return returnVector;
}
BossEnemy* EnemyManager::GetBossEnemyVector()
{
	BossEnemy* returnEnemy{};
	if (mBossEnemyUseFlag)
	{
		returnEnemy = mpBossEnemy.get();
	}
	return returnEnemy;
}
std::vector<SubordinateEnemy*> EnemyManager::GetUseSubordinateEnemyVector()
{
	std::vector<SubordinateEnemy*> returnVector{};
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		//未使用時は処理をしない
		if (!mpSubordinateEnemy[i]->GetUseFlag())continue;

		returnVector.push_back(mpSubordinateEnemy[i].get());
	}

	return returnVector;
}

/*===================================
ファイルから情報を取得する:private
引数：ファイルパス、カメラへのアドレス
返り値：なし
===================================*/
void EnemyManager::LoadFile(std::string filepath)
{
	//初期化
	DirectX::SimpleMath::Vector3 position = NOT_SET_ENEMY_POSITION;
	int phasenum = 0;


	//情報読み込み
	mpEnemyCall->LoadInfo(filepath);

	//BOSS生成処理
	mBossEnemyUseFlag = this->CreateBoss();

	
	//サイズを改めて指定
	//BOSSが存在する場合は余分にメモリを確保する
	if (mBossEnemyUseFlag)
	{
		mpEnemy.resize(mpEnemyCall->GetNormalEnemyStructerSize()+ ENEMY_ADDITIONAL_CAPACITY);
	}
	else
	{
		mpEnemy.resize(mpEnemyCall->GetNormalEnemyStructerSize());
	}	

	//生成
	int i = 0;
	for (i; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//情報が最大サイズになったら(これ以上敵情報がなければ)
		if (i == mpEnemyCall->GetNormalEnemyStructerSize()) 
		{
			//for文を抜ける。
			break;
		}
		position = mpEnemyCall.get()->GetNormalEnemyStructer(i).mVectorESPosition;
		phasenum = mpEnemyCall.get()->GetNormalEnemyStructer(i).mPhaseNumber;
		mpEnemy[i]->SetMovePhaseNumber(phasenum);
		mpEnemy[i]->Initialize(position);
	}



	//不要になったので削除
	mpEnemyCall->Reset();
}

/*======================================================================
ボス敵生成処理
引数：なし
返り値：生成フラグ
========================================================================*/
bool EnemyManager::CreateBoss()
{
	if (mpEnemyCall->GetBossEnemyStructer().mPhaseNumber == 0)return false;

	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 position = NOT_SET_ENEMY_POSITION;
	int phasenum = 0;

	//BOSS生成
	position = mpEnemyCall->GetBossEnemyStructer().mVectorESPosition;
	phasenum = mpEnemyCall->GetBossEnemyStructer().mPhaseNumber;
	mpBossEnemy->SetMovePhaseNumber(phasenum);
	mpBossEnemy->Initialize(position);

	return true;
}



/*==================================================
座標生成:private
引数：基準となる座標
返り値：生成座標
===================================================*/
DirectX::SimpleMath::Vector3 EnemyManager::CreatePosition(const DirectX::SimpleMath::Vector3& position)
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
	castPosition.x = static_cast<float>(randX(mt));
	castPosition.z = static_cast<float>(randZ(mt));

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


/*==================================================
配下敵の生存数チェック:private
引数：なし
返り値：生存数
===================================================*/
int EnemyManager::ChackSubordinateEnemyUseNum()
{
	int returnNum{ 0 };
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		//未使用時は処理をしない
		if (!mpSubordinateEnemy[i]->GetUseFlag())continue;

		returnNum++;
	}

	return returnNum;
}
