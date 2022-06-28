/*
ボス敵基本State　～移動～
作成者：杉山
作成日：2022/02/12
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

#include"EnemyMoveState/EnemyMoveStateRotation.h"
#include"EnemyMoveState/EnemyMoveStateWalk.h"
#include"EnemyMoveState/EnemyMoveStateWallAttack.h"

//列挙型の使用
#include"EnemyMainState.h"


//前方宣言
class EnemyMoveStateBase;	//状態State
class Block;				//引数

class BossEnemyMainStateAttack : public EnemyMainStateBase
{
private:

	//現在の状態
	EnemyMoveStateBase* mpEnemyMoveStateBase;
	EnemyMoveState mState;

	//状態分け


public:

	//コンストラクタ
	BossEnemyMainStateAttack();
	//デストラクタ
	~BossEnemyMainStateAttack();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//現在の状態
	EnemyMoveState GetMoveState()const { return mState; }

};
