/*
ボス敵用の状態Stateを管理する列挙型群
作成者：杉山
作成日：2022/02/12
*/
#pragma once

enum class BossEnemyMainState
{
	CREATE_BEFORE,	//生成前
	MOVE,			//移動
	ATTACK,			//攻撃
	CREATE,			//生成
	DISAPPEARANCE,	//消滅
};

enum class BossEnemyMoveState
{
	WALK,	//歩行
	ESCAPE,	//逃走
	STAND,	//立ち
};
