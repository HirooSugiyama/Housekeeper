/*
ボス敵移動State　～歩行～
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateEscape.h"
#include"../BossEnemyMainStateMove.h"

#include"../../BossEnemy.h"

//移動速度
const float BossEnemyMoveStateEscape::ENEMY_ESCAPE_SPEED = -0.25f;

//プレイヤーとの測定距離
const float BossEnemyMoveStateEscape::PLAYER_DISTANCE = 6.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemyMoveStateEscape::BossEnemyMoveStateEscape()
	:
	BossEnemyMoveStateBase()
	//()
{
}

/*===================================
デストラクタ
===================================*/
BossEnemyMoveStateEscape::~BossEnemyMoveStateEscape()
{

}

/*===================================
初期化処理
引数：敵のポインタ、ボス敵の行動State
返り値：なし
===================================*/
void BossEnemyMoveStateEscape::Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)
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
void BossEnemyMoveStateEscape::SetAngle()
{
	//向きを算出
	float angle = BossEnemyMoveStateBase::GetMoveState()->CalculationModelAngle();

	//なす角をモデルの角度にする
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->SetRotationY(angle);
}

/*===================================
逃走状態専用更新処理:private
引数：なし
返り値：なし
===================================*/
void BossEnemyMoveStateEscape::EscapeUpdate()
{
	//プレイヤーとの直線距離を求める
	DirectX::SimpleMath::Vector3 playerPosition =
		*BossEnemyMoveStateBase::GetMoveState()->GetSavePlayerPointer();

	DirectX::SimpleMath::Vector3 enemyPosition =
		BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->GetPosition();

	float distance{ 0.f };
	//距離を計測する
	distance = std::sqrtf((std::abs(playerPosition.x - enemyPosition.x)) * 2 +
		(std::abs(playerPosition.z - enemyPosition.z)) * 2);

	//指定の距離離れたら
	//一定距離におらず、追いかけ状態なら
	if (distance > PLAYER_DISTANCE)
	{
		//立ち状態にする
		BossEnemyMoveStateBase::GetMoveState()->ChangeStateWalk();
		dynamic_cast<BossEnemy*>(BossEnemyMoveStateBase::GetBossEnemy())->ChangeStateCreate();
	}
}

/*===================================
移動速度設定:private
引数：なし
返り値：移動ベクトル
===================================*/
DirectX::SimpleMath::Vector3 BossEnemyMoveStateEscape::GetMoveVelocity()
{

	//移動ベクトル取得
	DirectX::SimpleMath::Vector3 moveVelocity =
		BossEnemyMoveStateBase::GetMoveState()->CreateMoveVector(ENEMY_ESCAPE_SPEED);

	return moveVelocity;
}

