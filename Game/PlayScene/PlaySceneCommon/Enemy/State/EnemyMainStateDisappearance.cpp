/*
敵基本State　～消滅～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMainStateDisappearance.h"

//前方宣言
#include"../Enemy.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMainStateDisappearance::EnemyMainStateDisappearance()
	:EnemyMainStateBase()
	//,()
{
}

/*===================================
デストラクタ
===================================*/
EnemyMainStateDisappearance::~EnemyMainStateDisappearance()
{
}

/*===================================
初期化処理
引数：敵のポインタ
返り値：なし
===================================*/
void EnemyMainStateDisappearance::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateDisappearance::Update()
{

}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateDisappearance::Draw()
{
	//モデルの描画
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}