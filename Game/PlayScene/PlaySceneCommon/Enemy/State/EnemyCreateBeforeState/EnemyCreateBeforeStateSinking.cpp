/*
敵生成前State	～沈没～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyCreateBeforeStateSinking.h"

//前方宣言
#include"../../Enemy.h"

//影を拡大描画
const DirectX::SimpleMath::Vector2 EnemyCreateBeforeStateSinking::ENEMY_SHADOW_SCLAE_UP(1.5f, 1.5f);

//影の高さを調節
const float EnemyCreateBeforeStateSinking::ENEMY_SHADOW_SHIFT_POSITIONY = 1.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyCreateBeforeStateSinking::EnemyCreateBeforeStateSinking()
	:EnemyCreateBeforeStateBase()
	//,()
{
}

/*===================================
デストラクタ
===================================*/
EnemyCreateBeforeStateSinking::~EnemyCreateBeforeStateSinking()
{
}

/*=================================
初期化処理
引数：敵の行動State、敵のポインタ
返り値：なし
===================================*/
void EnemyCreateBeforeStateSinking::Initialize
(
	EnemyMainStateCreateBefore* pEnemyMainState,
	IEnemy* pEnemy
)
{
	//ポインタを保存
	EnemyCreateBeforeStateBase::SetEnemy(pEnemy);
	EnemyCreateBeforeStateBase::SetEnemyMainState(pEnemyMainState);

	//簡略化変数の宣言
	DirectX::SimpleMath::Vector2 baseScale = DirectX::SimpleMath::Vector2::Zero;

	//XZ平面に変換
	baseScale.x = EnemyCreateBeforeStateBase::GetEnemy()->GetEnemyModel()->GetScale().x;
	baseScale.y = EnemyCreateBeforeStateBase::GetEnemy()->GetEnemyModel()->GetScale().z;

	//影のサイズを変える
	EnemyCreateBeforeStateBase::GetEnemy()->
		GetShadow()->SetScale(baseScale * ENEMY_SHADOW_SCLAE_UP);	//XZ平面
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyCreateBeforeStateSinking::Draw()
{
	//簡略化変数の宣言
	DirectX::SimpleMath::Vector3 castPosition = EnemyCreateBeforeStateBase::GetEnemy()->
										GetEnemyModel()->GetPosition();
	castPosition.y = ENEMY_SHADOW_SHIFT_POSITIONY;

	EnemyCreateBeforeStateBase::GetEnemy()->GetShadow()->Draw(castPosition);
}