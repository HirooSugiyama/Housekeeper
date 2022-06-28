/*
ボス敵移動State　～歩行～
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateStand.h"

//関数の使用
#include"../../IEnemy.h"
#include"../BossEnemyMainStateMove.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemyMoveStateStand::BossEnemyMoveStateStand()
	:
	BossEnemyMoveStateBase()
{
}

/*===================================
デストラクタ
===================================*/
BossEnemyMoveStateStand::~BossEnemyMoveStateStand()
{
}

/*=============================================
初期化処理
引数：敵のポインタ、ボス敵の行動パターン
============================================*/
void BossEnemyMoveStateStand::Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)
{
	//ポインタ保存処理
	BossEnemyMoveStateBase::SetBossEnemy(pBossEnemy);
	BossEnemyMoveStateBase::SetMoveState(pMoveState);
}

/*===================================
向き設定処理:private
引数：なし
返り値：なし
===================================*/
void BossEnemyMoveStateStand::SetAngle()
{
	//向きを算出
	float angle = BossEnemyMoveStateBase::GetMoveState()->CalculationModelAngle();

	//なす角をモデルの角度にする
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->SetRotationY(angle);
}