/*
敵基本State　～移動～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

//列挙型の使用
#include"SubordinateEnemyState.h"

//状態分け
#include"SubordinateEnemyMoveState/SubordinateEnemyMoveStateStand.h"
#include"SubordinateEnemyMoveState/SubordinateEnemyMoveStateWalk.h"

//列挙型の使用
#include"SubordinateEnemyState.h"

//前方宣言
class SubordinateEnemyMoveStateBase;	//状態State基底クラス
class IEnemy;

class SubordinateEnemyMainStateMove : public EnemyMainStateBase
{

private:

	////現在の状態
	SubordinateEnemyMoveStateBase* mpMoveStateBase;
	SubordinateEnemyMoveState mState;
	
	//状態分け
	std::unique_ptr<SubordinateEnemyMoveStateStand> mpStand;
	std::unique_ptr<SubordinateEnemyMoveStateWalk> mpWalk;
	

public:

	//コンストラクタ
	SubordinateEnemyMainStateMove();
	//デストラクタ
	~SubordinateEnemyMainStateMove();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;


	//状態分け
	void ChangeStateStand()
	{
		mState = SubordinateEnemyMoveState::STAND;
		mpMoveStateBase = static_cast<SubordinateEnemyMoveStateBase*>(mpStand.get());
	}
	void ChangeStateWalk()
	{
		mState = SubordinateEnemyMoveState::WALK;
		mpMoveStateBase = static_cast<SubordinateEnemyMoveStateBase*>(mpWalk.get());
	}
	
	//アクセサ

	SubordinateEnemyMoveState GetState()const { return mState; }
	SubordinateEnemyMoveStateStand* GetStand()const { return mpStand.get(); }
	SubordinateEnemyMoveStateWalk* GetWalk()const { return mpWalk.get(); }

};
