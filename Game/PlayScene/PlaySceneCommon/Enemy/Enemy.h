/*
敵クラス
作成者：杉山
作成日：2021/10/21
*/

#pragma once


//継承元
#include"IEnemy.h"

//列挙型の使用
#include"StateEnemy.h"
#include"AngleEnemy.h"

//所持
#include"../ObjectModel/BoxModel.h"
//状態State
#include"State/EnemyMainStateMove.h"
#include"State/EnemyMainStateCreateBefore.h"
#include"State/EnemyMainStateMove.h"
#include"State/EnemyMainStateDamage.h"
#include"State/EnemyMainStateDisappearance.h"

//列挙型の使用
#include"State/EnemyMainState.h"
//前方宣言
class EnemyMainStateBase;	//状態分け基底クラス

struct AABB;				//関数の返り値で使用

class CameraBase;			//所持
class Enemy :public IEnemy
{
private:
	//定数
	//移動速度
	static const float ENEMY_MOVE_SPEED;

	//モデル描画範囲指定
	static const float ENEMY_MDEL_DROW_AREA;

	//ブロック番号保存数
	static const int ENEMY_SAVE_BLOCKNUMBER_MAX_NUM = 3;
	//ブロック番号例外数字
	static const int ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM;

	//敵モデルを強制的に横に向ける(向き反転する際に使用)
	static const float ENEMY_MODEL_FORCED_BESIDE;

	//敵のHP
	static const int ENEMY_HP;

	//反転数
	static const int REVERSE_NUM;

	//敵の攻撃力
	static const int ENEMY_ATTACK_NUM;


	//動き始めるフェーズ番号
	int mMovePhaseNumber;

	//状態
	//現在の状態
	EnemyMainStateBase* mpMainState;
	std::unique_ptr<EnemyMainStateCreateBefore> mpCreateBefore;
	std::unique_ptr<EnemyMainStateMove> mpMove;
	std::unique_ptr<EnemyMainStateDamage> mpDamage;
	std::unique_ptr<EnemyMainStateDisappearance> mpDisappearance;
	//状態管理列挙型
	EnemyMainState mState;


	//現在のモデルの向きを表す
	eAngleEnemy mEnemyModelAngle;

public:
	//関数
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize(const DirectX::SimpleMath::Vector3& position)override;
	//更新
	void Update()override;
	//描画
	void Draw()override;

	//ブロック攻撃処理
	void AttackBlock(Block* pBlock);

	//壁回避処理
	void AvoidanceBlock(Block* pBlock);

	//使用フラグを返す
	bool GetUseFlag() { return IEnemy::GetEnemyModel()->GetModelUseFlag(); }
	
	//アクセサ関連
	//状態分け
	void ChangeStateCreateBefore() override
	{ 
		mState = EnemyMainState::CREATE_BEFORE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpCreateBefore.get());
	}
	void ChangeStateMove()override
	{
		mState = EnemyMainState::MOVE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpMove.get());
	}
	void ChangeStateDamage()
	{
		mState = EnemyMainState::DAMAGE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpDamage.get());
		//ダメージ状態の最初の状態は必ず反動状態
		mpDamage->ChangeStateKnockBack();

	}
	void ChangeStateDisappearance()override
	{
		mState = EnemyMainState::DISAPPEARANCE;
		mpMainState = static_cast<EnemyMainStateBase*>(mpDisappearance.get());
	}

	//状態を取得
	EnemyMainState GetEnemyMainState()const { return mState; }


	EnemyMainStateCreateBefore* GetStateCreateBefore() const { return mpCreateBefore.get(); }
	EnemyMainStateMove* GetStateMove()const { return mpMove.get(); }
	EnemyMainStateDamage* GetStateDamage() const { return mpDamage.get(); }
	EnemyMainStateDisappearance* GetStateDisappearance() const { return mpDisappearance.get(); }

	//始動するフェーズ番号のアクセサ
	void SetMovePhaseNumber(const int& num){ mMovePhaseNumber = num; }
	int GetMovePhaseNumber()const {return mMovePhaseNumber;}

	//モデルの向きのアクセサ
	eAngleEnemy GetAngleEnemy()const { return mEnemyModelAngle; }
	void SetAngleEnemy(const eAngleEnemy& angle) { mEnemyModelAngle = angle; }

	//敵のHPのアクセサ
	int GetEnemyHP()override { return ENEMY_HP; }

	//移動処理
	void Move();

private:
	//モデルを設定する
	void SetEnemyModel();
};
