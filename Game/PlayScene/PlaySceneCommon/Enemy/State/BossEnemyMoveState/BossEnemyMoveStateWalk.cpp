/*
ボス敵移動State　～歩行～
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateWalk.h"

//関数の使用
#include"../../IEnemy.h"
#include"../BossEnemyMainStateMove.h"

//移動速度
const float BossEnemyMoveStateWalk::ENEMY_WALK_SPEED = 0.03f;

/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemyMoveStateWalk::BossEnemyMoveStateWalk()
	:
	BossEnemyMoveStateBase()
{
}

/*===================================
デストラクタ
===================================*/
BossEnemyMoveStateWalk::~BossEnemyMoveStateWalk()
{
}

/*===================================
初期化処理
引数：敵のポインタ、ボス敵の行動State
===================================*/
void BossEnemyMoveStateWalk::Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)
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
void BossEnemyMoveStateWalk::SetAngle()
{
	//向きを算出
	float angle = BossEnemyMoveStateBase::GetMoveState()->CalculationModelAngle();

	//なす角をモデルの角度にする
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->SetRotationY(angle);
}

/*===================================
移動速度設定:private
引数：なし
返り値：移動速度ベクトル
===================================*/
DirectX::SimpleMath::Vector3 BossEnemyMoveStateWalk::GetMoveVelocity()
{
	//移動ベクトル取得
	DirectX::SimpleMath::Vector3 moveVelocity = 
		BossEnemyMoveStateBase::GetMoveState()->CreateMoveVector(ENEMY_WALK_SPEED);

	return moveVelocity;
}
