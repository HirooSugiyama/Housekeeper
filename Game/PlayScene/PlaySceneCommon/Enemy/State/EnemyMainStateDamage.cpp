/*
敵基本State　～反動～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMainStateDamage.h"

//前方宣言
#include"../Enemy.h"


/*=================================
コンストラクタ
引数：なし
===================================*/
EnemyMainStateDamage::EnemyMainStateDamage()
	:
	EnemyMainStateBase(),
	mpKnockBack(),
	mpBlinking(),
	mpEnemyDamageStateBase(),
	mState()
{
	mpKnockBack = std::make_unique<EnemyDamageStateKnockBack>();
	mpBlinking = std::make_unique<EnemyDamageStateBlinking>();
}

/*===================================
デストラクタ
===================================*/
EnemyMainStateDamage::~EnemyMainStateDamage()
{
}

/*==================================
初期化処理
引数：敵のポインタ
返り値：なし
===================================*/
void EnemyMainStateDamage::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);


	//各状態の初期化処理
	mpKnockBack->Initialize(dynamic_cast<Enemy*>(pEnemy),this);
	mpBlinking->Initialize(dynamic_cast<Enemy*>(pEnemy),this);

	//最初は反動状態
	this->ChangeStateKnockBack();
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateDamage::Update()
{
	//現在の状態の更新処理
	mpEnemyDamageStateBase->Update();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateDamage::Draw()
{
	//現在の状態の描画処理
	mpEnemyDamageStateBase->Draw();
}