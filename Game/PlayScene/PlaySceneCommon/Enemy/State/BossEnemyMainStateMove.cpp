/*
ボス敵基本State　～移動～
作成者：杉山
作成日：2022/02/12
*/
#include"pch.h"
#include"BossEnemyMainStateMove.h"

//前方宣言
#include"EnemyMoveState/EnemyMoveStateBase.h"

//関数の使用
#include"../Enemy.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
BossEnemyMainStateMove::BossEnemyMainStateMove()
	:
	EnemyMainStateBase(),
	mpState(),
	mState(),
	mpWalk(),
	mpEscape(),
	mpStand()
{
	mpWalk = std::make_unique<BossEnemyMoveStateWalk>();
	mpEscape = std::make_unique<BossEnemyMoveStateEscape>();
	mpStand = std::make_unique<BossEnemyMoveStateStand>();
}

/*===================================
デストラクタ
===================================*/
BossEnemyMainStateMove::~BossEnemyMainStateMove()
{
}

/*===================================
初期化処理
引数：通常敵のポインタ
返り値：なし
===================================*/
void BossEnemyMainStateMove::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);

	//各状態の初期化処理
	mpWalk->Initialize(pEnemy, this);
	mpEscape->Initialize(pEnemy, this);
	mpStand->Initialize(pEnemy, this);


	//初期状態を設定
	this->ChangeStateWalk();
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMainStateMove::Update()
{
	//現在の状態の更新処理
	mpState->Update();
}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void BossEnemyMainStateMove::Draw()
{
	//現在の状態の描画処理
	mpState->Draw();
}

/*===================================
向き調節処理
引数：なし
返り値：向きベクトル
===================================*/
float BossEnemyMainStateMove::CalculationModelAngle()
{
	//中心点
	DirectX::SimpleMath::Vector3 position = *mpSavePlayerPointer;
	//中心点から今のいる位置のベクトル
	DirectX::SimpleMath::Vector3 vector =
		position - EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetPosition();
	int juge = -1;
	if (vector.z > 0)
	{
		juge = 1;
	}
	//法線ベクトル
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;

	//なす角
	float angle = std::acosf(vector.Dot(vel) / (vector.Length() * vel.Length()));

	//変換
	angle = DirectX::XMConvertToDegrees(angle* juge);

	angle += Utility::RIGHT_ANGLE;

	return angle;
}

/*===================================
移動ベクトル生成処理
引数：速度
返り値：実際の移動速度ベクトル
===================================*/
DirectX::SimpleMath::Vector3 BossEnemyMainStateMove::CreateMoveVector(const float& moveVelocity)
{
	//対象との距離を測定
	DirectX::SimpleMath::Vector3 distance;
	distance = *mpSavePlayerPointer -
		EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetPosition();

	distance.Normalize();		//正規化

	//スケーリング
	mChaseVelocity.x = distance.x * moveVelocity;
	mChaseVelocity.z = distance.z * moveVelocity;

	return mChaseVelocity;
}