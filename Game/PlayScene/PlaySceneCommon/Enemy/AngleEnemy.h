/*
敵のモデルの向きを管理する列挙を持つヘッダーファイル
作成日：2021/09/01
*/
#pragma once


//変更後の敵の向きを表す列挙型 
enum class eAngleEnemy
{
	STRAIGHT,
	LEFT,
	RIGHT,
};

//変えたい向きを保存する列挙型
enum class eChangeAfterAngle
{
	NONE,
	LEFT_ROTATION,
	RIGHT_ROTATION,
	STRAIGHT,
};

//敵の歩行状態を表す列挙型
enum class eEnemyWalkState
{
	GENERALLY,
	CHASING,
};
