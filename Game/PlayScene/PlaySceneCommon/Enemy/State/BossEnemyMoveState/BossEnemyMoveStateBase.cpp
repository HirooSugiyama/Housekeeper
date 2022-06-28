/*
ボス敵移動State基底クラス
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"

#include"BossEnemyMoveStateBase.h"

//前方宣言
#include"../../BossEnemy.h"
#include"../BossEnemyMainStateMove.h"


/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemyMoveStateBase::BossEnemyMoveStateBase()
	:
	mpMoveState(),
	mpEnemy()
{
}

/*===================================
デストラクタ
===================================*/
BossEnemyMoveStateBase::~BossEnemyMoveStateBase()
{
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMoveStateBase::Update()
{
	//移動ベクトル取得
	DirectX::SimpleMath::Vector3 moveVelocity = this->GetMoveVelocity();

	//そのまま設定
	BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->Move(moveVelocity);

	//向き調節処理
	this->SetAngle();

	//逃走状態専用更新処理
	this->EscapeUpdate();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMoveStateBase::Draw()
{
	//モデル描画
	mpEnemy->GetEnemyModel()->Draw();

	//影の描画
	BossEnemyMoveStateBase::GetBossEnemy()->GetShadow()->Draw
	(
		BossEnemyMoveStateBase::GetBossEnemy()->GetEnemyModel()->GetPosition()
	);

}
