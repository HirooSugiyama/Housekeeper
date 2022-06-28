/*
敵移動State　～壁攻撃～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMoveStateBase.h"

class Block;

class EnemyMoveStateWallAttack : public EnemyMoveStateBase
{
private:

	//攻撃インターバル
	static const int ENEMY_ATTACK_INTERVAL;

	//敵の攻撃力
	static const int ENEMY_ATTACK_POWER;


	//計測変数
	int mCurrentNum;

public:

	//コンストラクタ
	EnemyMoveStateWallAttack();
	//デストラクタ
	~EnemyMoveStateWallAttack()override;
	//初期化処理
	void Initialize(Enemy* pEnemy,EnemyMainStateMove* pEnemyMainState)override;
	//リセット処理
	void Reset()override;
	//更新処理
	void Update()override;

	//攻撃するタイミング計測関数
	bool AttackTiming();
};
