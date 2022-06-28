/*
ボス敵基本State　～移動～
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"
#include"BossEnemyMainStateCreate.h"

//前方宣言
#include"EnemyMoveState/EnemyMoveStateBase.h"

//関数の使用
#include"../Enemy.h"
#include "../BossEnemy.h"
#include "../SubordinateEnemy.h"


//回転速度
const float BossEnemyMainStateCreate::ROTATION_VELOCITY = 3.f;

//配列代表番号
const int BossEnemyMainStateCreate::ARRAY_REPRESENTATIVE_NUM = 0;

/*===================================
コンストラクタ
引数：なし
返り値：なし
===================================*/
BossEnemyMainStateCreate::BossEnemyMainStateCreate()
	:EnemyMainStateBase()
{
}

/*===================================
デストラクタ
===================================*/
BossEnemyMainStateCreate::~BossEnemyMainStateCreate()
{
}

/*===================================
初期化処理
引数：通常敵のポインタ
返り値：なし
===================================*/
void BossEnemyMainStateCreate::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMainStateCreate::Update()
{
	//回転させる
	float angle = EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY();
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle + ROTATION_VELOCITY);

	//短縮化(代表して0番の内容を使用)
	SubordinateEnemy* enemy = this->GetSubordinateEnemyAddress();
	if (enemy == nullptr)return;

	//状態変更処理
	if (enemy->GetState() == SubordinateEnemyMainState::MOVE)
	{
		EnemyMainStateBase::GetEnemy()->ChangeStateMove();
		dynamic_cast<BossEnemy*>(EnemyMainStateBase::GetEnemy())->GetStateMove()->ChangeStateWalk();
	}
}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMainStateCreate::Draw()
{
	//モデルの描画
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}

/*==================================
描画処理
引数：なし
返り値：配下敵のポインタ
===================================*/
SubordinateEnemy* BossEnemyMainStateCreate::GetSubordinateEnemyAddress()
{
	//簡略化
	BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(EnemyMainStateBase::GetEnemy());

	for (int i = 0; i < static_cast<int>(bossEnemy->GetSaveSubordinateEnemy().size()); i++)
	{
		//内容が入っていたら
		if (bossEnemy->GetSaveSubordinateEnemy().at(i) != nullptr)
		{
			return bossEnemy->GetSaveSubordinateEnemy().at(i);
		}
	}
	return nullptr;
}
