/*
配下敵クラス
作成者：杉山
作成日：2022/02/11
*/
#pragma once

//基底クラス
#include"IEnemy.h"

//状態State
#include"State/SubordinateEnemyMainStateMove.h"
#include"State/EnemyMainStateCreateBefore.h"
#include"State/EnemyMainStateDisappearance.h"

#include"State/SubordinateEnemyState.h"

//前方宣言
//基底クラス
class EnemyMainStateBase;	//状態分け基底クラス

class SubordinateEnemy :public IEnemy
{
private:

	//配下敵のHP
	static const int SUBORDINATE_ENEMY_HP;

	//現在の状態
	EnemyMainStateBase* mpState;
	SubordinateEnemyMainState mState;

	//状態State
	std::unique_ptr<EnemyMainStateCreateBefore> mpCrateBefore;
	std::unique_ptr<SubordinateEnemyMainStateMove> mpMove;
	std::unique_ptr<EnemyMainStateDisappearance> mpDisappearance;

public:

	//コンストラクタ
	SubordinateEnemy();
	//デストラクタ
	~SubordinateEnemy()override;
	//初期化処理
	void Initialize(const DirectX::SimpleMath::Vector3& position)override;

	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//使用フラグの取得
	bool GetUseFlag() { return IEnemy::GetEnemyModel()->GetModelUseFlag(); }


	//状態変更処理
	void ChangeStateCreateBefore()override
	{
		mState = SubordinateEnemyMainState::CREATE_BEFORE;
		mpState = static_cast<EnemyMainStateBase*>(mpCrateBefore.get());
	}
	void ChangeStateMove()override
	{
		mState = SubordinateEnemyMainState::MOVE;
		mpState = static_cast<EnemyMainStateBase*>(mpMove.get());
	}
	void ChangeStateDisappearance()override
	{
		mState = SubordinateEnemyMainState::DISAPPEARANCE;
		mpState = static_cast<EnemyMainStateBase*>(mpDisappearance.get());
	}


	//状態処理のアクセサ
	SubordinateEnemyMainState GetState() const { return mState; }
	EnemyMainStateCreateBefore* GetStateCrateBefore()const { return mpCrateBefore.get(); }
	SubordinateEnemyMainStateMove* GetStateMove()const { return mpMove.get(); }
	EnemyMainStateDisappearance* GetStateDisappearance()const { return mpDisappearance.get(); }


	//敵のHPのアクセサ
	int GetEnemyHP() override{ return SUBORDINATE_ENEMY_HP; }

private:
	//当たり判定設定
	void SetCollider();
};
