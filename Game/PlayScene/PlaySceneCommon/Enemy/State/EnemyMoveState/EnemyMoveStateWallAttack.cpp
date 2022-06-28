/*
敵移動State　～壁攻撃～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMoveStateWallAttack.h"

//前方宣言
#include"../../Enemy.h"


//攻撃インターバル
const int EnemyMoveStateWallAttack::ENEMY_ATTACK_INTERVAL = 60;

//敵の攻撃力
const int EnemyMoveStateWallAttack::ENEMY_ATTACK_POWER = 1;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMoveStateWallAttack::EnemyMoveStateWallAttack()
	:
	EnemyMoveStateBase(),
	mCurrentNum(0)
{
}

/*===================================
デストラクタ
===================================*/
EnemyMoveStateWallAttack::~EnemyMoveStateWallAttack()
{
}

/*===================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void EnemyMoveStateWallAttack::Initialize
(
	Enemy* pEnemy,
	EnemyMainStateMove* pEnemyMainState
)
{
	//ポインタを保存する
	EnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);
	EnemyMoveStateBase::SetEnemy(pEnemy);

}

/*===================================
リセット処理
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWallAttack::Reset()
{
	//正面を向ける
	EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(EnemyMoveStateBase::GetFrontAngle());

}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWallAttack::Update()
{
	bool flag = *EnemyMoveStateBase::GetEnemyMainState()->GetAttackBlock();
	if (flag)
	{
		mCurrentNum++;
	}
	//対象の壁が未使用状態となったら
	else
	{
		//歩行状態へ
		EnemyMoveStateBase::GetEnemyMainState()->ChangeStateWalk();
		
	}

}

/*=============================================
攻撃するタイミング計測関数
引数：なし
返り値：攻撃するか否か(true：攻撃する)
=============================================*/
bool EnemyMoveStateWallAttack::AttackTiming()
{

	//攻撃するタイミングが来たら
	if (mCurrentNum >= ENEMY_ATTACK_INTERVAL)
	{
		//値を初期化して
		mCurrentNum = 0;

		return true;
	}

	return false;
}
