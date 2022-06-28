/*
敵行動パターンの列挙型の管理ヘッダーファイル
作成日：2021/09/01
*/
#pragma once



enum class eStateEnemy
{
	WALK,
	ROTATION,
	KNOCK_BACK,
	APPEARANCE,
	ATTACK,
	BURIED,
	BLINKING, 
};

