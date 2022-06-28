/*
配下敵の状態を表す列挙型
作成者：杉山
作成日：2022/02/13
*/
#pragma once


enum class SubordinateEnemyMainState
{
	CREATE_BEFORE,	//生成前
	MOVE,			//移動
	DISAPPEARANCE,	//消滅
};

enum class SubordinateEnemyMoveState
{
	STAND,	//立ち
	WALK	//歩き状態
};