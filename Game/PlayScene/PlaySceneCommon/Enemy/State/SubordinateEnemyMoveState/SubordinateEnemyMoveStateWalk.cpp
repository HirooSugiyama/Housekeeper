/*
配下敵移動State　～歩行～
作成者：杉山
作成日：2022/02/14
*/
#include"pch.h"

#include"SubordinateEnemyMoveStateWalk.h"

//関数の使用
#include"../../IEnemy.h"
#include"../SubordinateEnemyMainStateMove.h"

//移動速度
const float SubordinateEnemyMoveStateWalk::SUBORDINATE_ENEMY_MOVE_VELOCITY = 0.05f;

//向き調整係数
const int SubordinateEnemyMoveStateWalk::ANGLE_SHIFT = 1;

/*===================================
コンストラクタ
引数：なし
===================================*/
SubordinateEnemyMoveStateWalk::SubordinateEnemyMoveStateWalk()
	:
	SubordinateEnemyMoveStateBase(),
	mChaseVelocity(),
	mpSavePlayerPointer()
{
}

/*===================================
デストラクタ
===================================*/
SubordinateEnemyMoveStateWalk::~SubordinateEnemyMoveStateWalk()
{
}

/*===================================
初期化処理
引数：敵のポインタ、敵の行動State
返り値：なし
===================================*/
void SubordinateEnemyMoveStateWalk::Initialize(IEnemy* pEnemy, SubordinateEnemyMainStateMove* pEnemyMainState)
{
	//アドレス保存
	SubordinateEnemyMoveStateBase::SetEnemy(pEnemy);
	SubordinateEnemyMoveStateBase::SetEnemyMainState(pEnemyMainState);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemyMoveStateWalk::Update()
{
	//移動処理
	this->Move();

	//向き調節処理
	this->CalculationModelAngle();
}


/*===================================
移動処理
引数：なし
返り値：なし
===================================*/
void SubordinateEnemyMoveStateWalk::Move()
{
	//対象との距離を測定
	DirectX::SimpleMath::Vector3 distance;
	distance = *mpSavePlayerPointer -
		SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	distance.Normalize();		//正規化

	//スケーリング
	mChaseVelocity.x = distance.x * SUBORDINATE_ENEMY_MOVE_VELOCITY;
	mChaseVelocity.z = distance.z * SUBORDINATE_ENEMY_MOVE_VELOCITY;

	//移動処理
	SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->Move(mChaseVelocity);
}

/*===================================
向き調節処理:private
引数：なし
返り値：なし
===================================*/
void SubordinateEnemyMoveStateWalk::CalculationModelAngle()
{
	//中心点
	DirectX::SimpleMath::Vector3 position = *mpSavePlayerPointer;
	//中心点から今のいる位置のベクトル
	DirectX::SimpleMath::Vector3 vector =
		position - SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	//法線ベクトル
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;

	int juge = Utility::EXCEPTION_NUM;
	if (vector.z > 0)
	{
		juge = ANGLE_SHIFT;
	}


	//なす角
	float angle = std::acosf(vector.Dot(vel) / (vector.Length() * vel.Length()));

	//変換
	angle = DirectX::XMConvertToDegrees(angle * juge);

	angle += Utility::RIGHT_ANGLE;

	//移動処理
	SubordinateEnemyMoveStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle);
}