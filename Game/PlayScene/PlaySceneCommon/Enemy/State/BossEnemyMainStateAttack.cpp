/*
ボスs敵基本State　～移動～
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"
#include"BossEnemyMainStateAttack.h"

//前方宣言
#include"EnemyMoveState/EnemyMoveStateBase.h"

//関数の使用
#include"../Enemy.h"


/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemyMainStateAttack::BossEnemyMainStateAttack()
	:EnemyMainStateBase()
	, mpEnemyMoveStateBase()
	, mState(EnemyMoveState::WALK)
{
}

/*===================================
デストラクタ
===================================*/
BossEnemyMainStateAttack::~BossEnemyMainStateAttack()
{
}

/*===================================
初期化処理
引数：通常敵のポインタ
返り値：なし
===================================*/
void BossEnemyMainStateAttack::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMainStateAttack::Update()
{

}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMainStateAttack::Draw()
{
	//モデルの描画
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}
