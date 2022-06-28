/*
敵基本State　～移動～
作成者：杉山
作成日：2022/02/07
*/
#include"pch.h"
#include"EnemyMainStateMove.h"

//前方宣言
#include"EnemyMoveState/EnemyMoveStateBase.h"

//関数の使用
#include"../Enemy.h"


//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
const DirectX::SimpleMath::Vector3 EnemyMainStateMove::ESTATE_COLLIDER_POSITION(0.f, 0.f, 1.f);

//拡大率(当たり判定)
const DirectX::SimpleMath::Vector3 EnemyMainStateMove::ESTATE_COLLIDER_SCALE(0.25f, 0.125f, 0.125f);

//連続衝突防止用移動定数
const DirectX::SimpleMath::Vector3 EnemyMainStateMove::HIT_STOP_SHIFT(0.5f,0.f,0.f);

//反転角度
const float EnemyMainStateMove::REVERSE_ANGLE = 180.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
EnemyMainStateMove::EnemyMainStateMove()
	:EnemyMainStateBase()
	, mpEnemyMoveStateBase()
	, mState(EnemyMoveState::WALK)
	, mpRotation()
	, mpWalk()
	, mpAttack()
	, mMoveCollider()
	, mpFirstHitBlock()
	, mReverseNum()
	, mBlockHitFlag(EnemyBlockHit::NONE)
	, mpAttackBlockUseFlag(nullptr)
{
	mpRotation = std::make_unique<EnemyMoveStateRotation>();
	mpWalk = std::make_unique<EnemyMoveStateWalk>();
	mpAttack = std::make_unique<EnemyMoveStateWallAttack>();
}

/*===================================
デストラクタ
===================================*/
EnemyMainStateMove::~EnemyMainStateMove()
{
}

/*===================================
初期化処理
引数：敵のポインタ
返り値：なし
===================================*/
void EnemyMainStateMove::Initialize(IEnemy* pEnemy)
{
	//ポインタを保存
	EnemyMainStateBase::SetEnemy(pEnemy);

	//各状態の初期化処理
	mpRotation->Initialize(dynamic_cast<Enemy*>(pEnemy),this);
	mpWalk->Initialize(dynamic_cast<Enemy*>(pEnemy),this);
	mpAttack->Initialize(dynamic_cast<Enemy*>(pEnemy),this);


	//初期状態を設定
	this->ChangeStateWalk();
}

/*==================================
更新処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateMove::Update()
{
	//直前まで衝突していた場合
	if (mBlockHitFlag == EnemyBlockHit::NOT_HIT&& &mpAttackBlockUseFlag==false)
	{
		//初期化して
		mBlockHitFlag = EnemyBlockHit::NONE;

		//回転処理へ
		this->ChangeStateRotation();

		mpFirstHitBlock = nullptr;
	}

	//現在の状態の更新処理を行う
	mpEnemyMoveStateBase->Update();


	//衝突しなくなった場合の処理
	this->NotHitEnemyChangeStateRotation();

	if (mState == EnemyMoveState::WALK)
	{
		//当たり判定更新処理
		this->SetAABBCollider();
	}
}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void EnemyMainStateMove::Draw()
{
	//モデルの描画
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->Draw();
}

/*==================================
向きを反転する
引数：なし
返り値：なし
===================================*/
void EnemyMainStateMove::ReverseAngle()
{
	float angle = EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY();
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle + REVERSE_ANGLE);

	//360度補正
	if (EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY() > 360.f)
	{
		angle = EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetRotAngleY() - 360.f;
		EnemyMainStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(angle);
	}

	//反転数追加
	mReverseNum++;

	//移動量を再設定
	mpWalk->CalculationMoveVelocity();

	this->Update();
}

/*============================
向きを初期化
引数：なし
返り値：なし
============================*/
void EnemyMainStateMove::ResetEnemyAngle()
{
	//正面を向ける
	EnemyMainStateBase::GetEnemy()->GetEnemyModel()->SetRotationY(mpEnemyMoveStateBase->GetFrontAngle());
}


/*==============================================
衝突しなくなった場合回転させる：private
引数：なし
返り値：なし
===============================================*/
void EnemyMainStateMove::NotHitEnemyChangeStateRotation()
{
	//反転回数が増加している場合も通さない
	if (mReverseNum >= 2)return;

	if (mState == EnemyMoveState::WALL_ATTACK)return;

	if (mBlockHitFlag == EnemyMainStateMove::EnemyBlockHit::NOT_HIT)
	{
		//回転に切り替える
		this->ChangeStateRotation();
		this->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NONE);
	}
}

/*==================================
当たり判定を設定する：private
引数：なし
返り値：なし
===================================*/
void EnemyMainStateMove::SetAABBCollider()
{
	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 min, max;

	//借り入れ用変数の宣言
	DirectX::SimpleMath::Vector3 position, scale;

	//簡略化
	position = EnemyMainStateBase::GetEnemy()->GetEnemyModel()->GetPosition() + ESTATE_COLLIDER_POSITION;
	scale = ESTATE_COLLIDER_SCALE;


	//当たり判定の座標を算出
	min = position - scale;
	max = position + scale;

	//当たり判定を代入する
	mMoveCollider.SetCollider(min, max);
}