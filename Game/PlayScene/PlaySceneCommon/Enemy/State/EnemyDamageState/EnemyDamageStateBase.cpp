/*
敵ダメージState基底クラス
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyDamageStateBase.h"

//前方宣言
#include"../EnemyMainStateMove.h"
#include"../../Enemy.h"


/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyDamageStateBase::EnemyDamageStateBase()
	:mpEnemyMainState()
	, mpEnemy()
{
}

/*===================================
デストラクタ
===================================*/
EnemyDamageStateBase::~EnemyDamageStateBase()
{
}