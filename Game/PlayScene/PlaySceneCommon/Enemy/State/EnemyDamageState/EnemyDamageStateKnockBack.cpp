/*
敵ダメージState　～反動～
作成者：杉山
作成日：2022/02/09
*/
#include"pch.h"
#include "EnemyDamageStateKnockBack.h"

//関数の使用
#include"../../Enemy.h"


//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
const DirectX::SimpleMath::Vector3 EnemyDamageStateKnockBack::ESTATE_COLLIDER_POSITION(0.f, 0.f, 1.f);

//拡大率(当たり判定)
const DirectX::SimpleMath::Vector3 EnemyDamageStateKnockBack::ESTATE_COLLIDER_SCALE(0.525f, 0.125f, 0.125f);

//移動速度
const float EnemyDamageStateKnockBack::ENEMY_MOVE_SPEED = 0.5f;

//速度減少率
const float EnemyDamageStateKnockBack::ENEMY_MOVE_SPEED_DECREASE = 0.7f;

//速度最小値
const float EnemyDamageStateKnockBack::ENEMY_MIN_VELOCITY = 0.0001f;

//移動ベクトルを小さくする
const float EnemyDamageStateKnockBack::ENEMY_MOVE_VELOCITY_SMALL = 0.5f;

//移動ベクトルを反転させる
const float EnemyDamageStateKnockBack::ENEMY_MOVE_VELOCITY_REVERSE = -1.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyDamageStateKnockBack::EnemyDamageStateKnockBack()
	:
	EnemyDamageStateBase(),
	mMoveVec()
{
}

/*===================================
デストラクタ
===================================*/
EnemyDamageStateKnockBack::~EnemyDamageStateKnockBack()
{
}

/*==================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void EnemyDamageStateKnockBack::Initialize(Enemy* pEnemy, EnemyMainStateDamage* pEnemyMainState)
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
void EnemyDamageStateKnockBack::Reset()
{
	mMoveVec = DirectX::SimpleMath::Vector3::Zero;
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyDamageStateKnockBack::Update()
{
	//変換用変数の宣言
	DirectX::SimpleMath::Vector3 vel;

	vel -= mMoveVec;

	//速度を減少させる
	mMoveVec *= ENEMY_MOVE_SPEED_DECREASE;

	//モデルを移動させる
	EnemyDamageStateBase::GetEnemy()->GetEnemyModel()->Move(vel);

	//もし速度が0に近づいたら
	if (this->Vector3Max(mMoveVec) <= ENEMY_MIN_VELOCITY)
	{
		//歩き状態へ
		EnemyDamageStateBase::GetEnemyMainState()->ChangeStateBlinking();
	}
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyDamageStateKnockBack::Draw()
{
	//モデルの描画
	EnemyDamageStateBase::GetEnemy()->GetEnemyModel()->Draw();
}


/*=======================
移動ベクトル保存用変数
引数：移動ベクトル
返り値：なし
=========================*/
void EnemyDamageStateKnockBack::SetMoveVector(const DirectX::SimpleMath::Vector3& movevec)
{
	mMoveVec = movevec;
}

/*====================================================
移動ベクトルをスケーリング
引数：なし
返り値：なし
====================================================*/
void EnemyDamageStateKnockBack::MoveVectorScaling()
{
	//正規化
	mMoveVec.Normalize();

	//反転
	mMoveVec *= ENEMY_MOVE_VELOCITY_REVERSE;

	//スケーリング
	mMoveVec *= ENEMY_MOVE_VELOCITY_SMALL;
}

/*====================================================
Vector3のうちの最も大きい値を返す関数:private
引数：Vector3型の値
返り値：引数内の最大値
====================================================*/
float EnemyDamageStateKnockBack::Vector3Max(const DirectX::SimpleMath::Vector3& num)
{
	//初期値としてXの値を入れる
	float returnnum = std::fabs(num.x);

	//Yのほうが大きければ
	if (returnnum < std::fabs(num.y))
	{
		//Yを入れる
		returnnum = num.y;
	}
	//Zのほうが大きければ
	if (returnnum < std::fabs(num.z))
	{
		//Zを入れる
		returnnum = num.z;
	}

	//最大値を返す
	return returnnum;
}

