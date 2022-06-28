/*
状態Stateを管理する列挙型群
作成者：杉山
作成日：2022/02/07
*/
#pragma once



enum class EnemyMainState
{
	CREATE_BEFORE,	//生成前
	MOVE,			//移動
	DAMAGE,			//反動
	DISAPPEARANCE,	//消滅
};


enum class EnemyCreateBeforeState
{
	APPEARANCE,	//出現
	SINKING		//沈没
};

enum class EnemyMoveState
{
	WALK,		//歩行
	ROTATION,	//回転
	WALL_ATTACK	//壁攻撃
};

enum class EnemyDamageState
{
	KNOCK_BACK,	//反動
	BLINKING,	//点滅
};