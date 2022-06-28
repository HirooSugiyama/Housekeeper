/*
敵移動State　～歩行～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMoveStateWalk.h"

//前方宣言
#include"../../Enemy.h"



//移動速度
const float EnemyMoveStateWalk::ENEMY_MOVE_SPEED = 0.03f;

const float EnemyMoveStateWalk::SHIFT_ANGLE = 270.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMoveStateWalk::EnemyMoveStateWalk()
	:EnemyMoveStateBase()
	, mPlayerChaseFlag()
	, mChaseVelocity()
	, mEnemyMoveVelocity()
	, mChasePlayerPositon(nullptr)
{
}

/*===================================
デストラクタ
===================================*/
EnemyMoveStateWalk::~EnemyMoveStateWalk()
{
}

/*===================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void EnemyMoveStateWalk::Initialize
(
	Enemy* pEnemy,
	EnemyMainStateMove* pEnemyMainState
)
{
	//ポインタを保存する
	EnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);
	EnemyMoveStateBase::SetEnemy(pEnemy);
}

/*==================================
State変更前のリセット処理
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWalk::Reset()
{
	//移動量を算出する
	this->CalculationMoveVelocity();

	//追跡フラグを下す
	mPlayerChaseFlag = false;
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWalk::Update()
{
	//追いかけ状態ならば
	if (mPlayerChaseFlag)
	{
		//追尾速度設定
		this->ChaseVelocity();

		//向き指定
		this->RotEnemyForTarget();

		//追尾処理
		this->Chase();
	}
	else
	{
		//移動処理
		this->Move();
	}
}

/*=====================
向きを変更する
引数：対象の座標
返り値：なし
======================*/
void EnemyMoveStateWalk::RotEnemyForTarget()
{
	//中心点
	DirectX::SimpleMath::Vector3 nierPosition = *mChasePlayerPositon;
	//中心点から今のいる位置のベクトル
	DirectX::SimpleMath::Vector3 toVec = nierPosition - EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	//もし、対象が敵より奥にいる状態ならば敵は直進とする
	if (toVec.z <= 0)
	{
		//追跡フラグを下す
		mPlayerChaseFlag = false;

		//向きをリセットする
		EnemyMoveStateBase::GetEnemyMainState()->ResetEnemyAngle();
	}
	else
	{
		//法線ベクトル
		DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;
		//なす角
		float angle = std::acosf(toVec.Dot(vel) / (toVec.Length() * vel.Length()));
		angle = DirectX::XMConvertToDegrees(angle) + Utility::RIGHT_ANGLE;
		//なす角をモデルの角度にする
		EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle);
	}
}


/*==================================
移動量を算出
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWalk::CalculationMoveVelocity()
{
	//現在の角度を取得
	float angle = EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY();

	//360度補正
	if (angle > 360.f)
	{
		angle = EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY() - 360.f;
		EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle);
	}

	//ラジアン変換
	angle = DirectX::XMConvertToRadians(angle + SHIFT_ANGLE);

	//移動量を生成
	mEnemyMoveVelocity.x = cosf(angle);
	mEnemyMoveVelocity.z = sinf(angle);
	mEnemyMoveVelocity.x *= -ENEMY_MOVE_SPEED;
	mEnemyMoveVelocity.z *= ENEMY_MOVE_SPEED;
}


/*==================================
追尾速度設定：private
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWalk::ChaseVelocity()
{
	//対象との距離を測定
	DirectX::SimpleMath::Vector3 distance;
	distance = *mChasePlayerPositon - EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	distance.Normalize();		//正規化

	mChaseVelocity.x = distance.x * ENEMY_MOVE_SPEED;
	mChaseVelocity.z = distance.z * ENEMY_MOVE_SPEED;
}

/*===================================
移動処理：private
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWalk::Move()
{
	//移動させる
	EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->Move(mEnemyMoveVelocity);
}

/*===================================
追尾処理：private
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateWalk::Chase()
{
	//移動させる
	EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->Move(mChaseVelocity);
}
