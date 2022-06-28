/*
敵基本State　～移動～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"SubordinateEnemyMainStateMove.h"

//前方宣言
#include"EnemyMoveState/EnemyMoveStateBase.h"
#include"SubordinateEnemyMoveState/SubordinateEnemyMoveStateBase.h"

//関数の使用
#include"../IEnemy.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
SubordinateEnemyMainStateMove::SubordinateEnemyMainStateMove()
	:
	EnemyMainStateBase(),
	mpMoveStateBase(),
	mState(),
	mpStand(),
	mpWalk()
{	
	mpStand = std::make_unique<SubordinateEnemyMoveStateStand>();
	mpWalk = std::make_unique<SubordinateEnemyMoveStateWalk>();
}

/*===================================
デストラクタ
===================================*/
SubordinateEnemyMainStateMove::~SubordinateEnemyMainStateMove()
{
}

/*===================================
初期化処理
引数：敵のポインタ
返り値：なし
===================================*/
void SubordinateEnemyMainStateMove::Initialize(IEnemy* pEnemy)
{
	//ポインタ保存
	EnemyMainStateBase::SetEnemy(pEnemy);

	//状態の初期化処理
	mpStand->Initialize(pEnemy,this);
	mpWalk->Initialize(pEnemy,this);

	//最初の状態は歩行状態
	this->ChangeStateWalk();
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemyMainStateMove::Update()
{
	//現在の状態の更新処理
	mpMoveStateBase->Update();
}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemyMainStateMove::Draw()
{
	//モデルの描画
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}

