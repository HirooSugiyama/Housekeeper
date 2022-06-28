/*
敵ダメージState　～反動～
作成者：杉山
作成日：2022/02/09
*/
#include"pch.h"
#include "EnemyDamageStateBlinking.h"

//関数の使用
#include"../../Enemy.h"

//プレイヤー点滅インターバル
const int EnemyDamageStateBlinking::ENEMY_BLINKING_INTERVAL = 10;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyDamageStateBlinking::EnemyDamageStateBlinking()
	:
	EnemyDamageStateBase(),
	mpDamageTimer(nullptr)
{
	mpDamageTimer = std::make_unique<DamageTimer>();
}

/*===================================
デストラクタ
===================================*/
EnemyDamageStateBlinking::~EnemyDamageStateBlinking()
{
}

/*===================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void EnemyDamageStateBlinking::Initialize(Enemy* pEnemy, EnemyMainStateDamage* pEnemyMainState)
{
	//ポインタを保存
	EnemyDamageStateBase::SetEnemyMainState(pEnemyMainState);
	EnemyDamageStateBase::SetEnemy(pEnemy);
}

/*===================================
リセット処理
引数：なし
返り値：なし
===================================*/
void EnemyDamageStateBlinking::Reset()
{
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyDamageStateBlinking::Update()
{
	//点滅処理を持ち主に送る
	bool flag = mpDamageTimer->RegularIntervalTimer(ENEMY_BLINKING_INTERVAL);
	EnemyDamageStateBase::GetEnemy()->GetEnemyModel()->SetDrawFlag(flag);

	//時間が来たら
	if (mpDamageTimer->Update())
	{
		//描画フラグを建てる
		EnemyDamageStateBase::GetEnemy()->GetEnemyModel()->SetDrawFlag(true);
		//時間が来たら立ち状態に戻す
		EnemyDamageStateBase::GetEnemy()->ChangeStateMove();
		//正面を向ける
		EnemyDamageStateBase::GetEnemy()->GetStateMove()->ResetEnemyAngle();
		//歩き状態に
		EnemyDamageStateBase::GetEnemy()->GetStateMove()->ChangeStateWalk();
		//最初に当たった壁のアドレスを無効化する
		EnemyDamageStateBlinking::GetEnemy()->GetStateMove()->SetFirstHitBlock(nullptr);
		EnemyDamageStateBlinking::GetEnemy()->GetStateMove()->SetAttackBlock(nullptr);

		//敵の更新処理を一度だけ回す
		EnemyDamageStateBlinking::GetEnemy()->Update();
	}
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyDamageStateBlinking::Draw()
{
	//モデルの描画
	EnemyDamageStateBase::GetEnemy()->GetEnemyModel()->Draw();
}
