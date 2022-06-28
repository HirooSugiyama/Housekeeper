/*
敵移動State基底クラス
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMoveStateBase.h"

//前方宣言
#include"../EnemyMainStateMove.h"
#include"../../Enemy.h"


//正面
const float EnemyMoveStateBase::FRONT = 180.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMoveStateBase::EnemyMoveStateBase()
	:mpEnemyMainState()
	, mpEnemy()
{
}

/*===================================
デストラクタ
===================================*/
EnemyMoveStateBase::~EnemyMoveStateBase()
{
}