/*
敵生成前State基底クラス
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyCreateBeforeStateBase.h"

//前方宣言
#include"../EnemyMainStateCreateBefore.h"

//関数の使用
#include"../../IEnemy.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyCreateBeforeStateBase::EnemyCreateBeforeStateBase()
	:mpEnemyMainState()
	, mpEnemy()
{
}

/*===================================
デストラクタ
===================================*/
EnemyCreateBeforeStateBase::~EnemyCreateBeforeStateBase()
{
}