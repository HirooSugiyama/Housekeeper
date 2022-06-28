/*
敵移動State　～回転～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMoveStateRotation.h"

//前方宣言
#include"../../Enemy.h"

//拡大率(当たり判定)
const DirectX::SimpleMath::Vector3 EnemyMoveStateRotation::ESTATE_COLLIDER_SCALE(0.25f, 0.125f, 0.125f);

//回転スピード
const float EnemyMoveStateRotation::ESTATE_ROT_SPEED = 1.5f;

const float EnemyMoveStateRotation::ROTATION_AFTER_ANGLE = 90.f;


/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMoveStateRotation::EnemyMoveStateRotation()
	:EnemyMoveStateBase()
	, mRotationNowAngle()
	, mRotationAngle()
	, mRotationVelocity()
{
}

/*===================================
デストラクタ
===================================*/
EnemyMoveStateRotation::~EnemyMoveStateRotation()
{
}

/*==================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void EnemyMoveStateRotation::Initialize
(
	Enemy* pEnemy,
	EnemyMainStateMove* pEnemyMainState
)
{
	//ポインタを保存する
	EnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);
	EnemyMoveStateBase::SetEnemy(pEnemy);

	//乱数でどっちを向くかを決める
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	
}
/*===================================
State変更前のリセット処理
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateRotation::Reset()
{
	//現在の角度を初期化
	mRotationNowAngle = 0.f;
	mRotationVelocity = 0.f;

	//現在の角度で処理を変える
	float rotation = EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY();

	//正面を向いていたら
	if (rotation == EnemyMoveStateBase::GetFrontAngle())
	{
		//回転する方向を初期化
		mRotationAngle = RotationAngle::NUM;

		//回転方向を決める
		this->ConfigurationRotationAngle();
	}
	//それ以外の場合は
	else
	{
		//足して正面になる場合は左向きなので
		if (rotation + ROTATION_AFTER_ANGLE== EnemyMoveStateBase::GetFrontAngle())
		{
			mRotationAngle = RotationAngle::LEFT;
			
		}
		//足して正面にならない場合は右向きなので
		else
		{
			mRotationAngle = RotationAngle::RIGHT;
		}
	}
	//回転する方向によって速度を決める
	this->ConfigurationRotationVelocity();
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateRotation::Update()
{
	//回転させる
	float angle = EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY();
	EnemyMoveStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle + mRotationVelocity);


	//増加量を更新する
	mRotationNowAngle += ESTATE_ROT_SPEED;
	//最大角度となったら
	if (mRotationNowAngle >= ROTATION_AFTER_ANGLE)
	{
		//歩行状態に
  		EnemyMoveStateBase::GetEnemyMainState()->ChangeStateWalk();
	}

}

/*===================================
回転方向を決める:private
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateRotation::ConfigurationRotationAngle()
{
	mRotationAngle =
		static_cast<RotationAngle>
		(
			static_cast<bool>(rand() % static_cast<int>(RotationAngle::NUM))
		);
}

/*===================================
向きに応じて回転速度を決める:private
引数：なし
返り値：なし
===================================*/
void EnemyMoveStateRotation::ConfigurationRotationVelocity()
{
	switch (mRotationAngle)
	{
		case RotationAngle::LEFT:
		{
			mRotationVelocity += ESTATE_ROT_SPEED;
			break;
		}
		case RotationAngle::RIGHT:
		{
			mRotationVelocity -= ESTATE_ROT_SPEED;
			break;
		}
		case RotationAngle::NUM:break;
	}
	
}
