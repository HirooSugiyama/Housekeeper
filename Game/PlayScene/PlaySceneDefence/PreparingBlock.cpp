/*
プレイヤーのブロック生成周りの処理
作成者：杉山
作成日：2021/06/18
*/

#include"pch.h"
#include "PreparingBlock.h"

//移動速度の取得に使用
#include"../PlaySceneCommon/ObjectMove.h"

//関数内で使用
#include"../PlaySceneCommon/GridLine/GridLineManager.h"

//所持金の取得
#include"Game/Money/Money.h"






//ブロック生成必要資材数
const int PreparingBlock::BLOCK_CREATE_MONEY_NUM = 10;

//プレイヤーから少しずらす座標
const DirectX::SimpleMath::Vector3   PreparingBlock::BLOCK_SHIFT_PLAYERPOSITION(0.f, 0.5f, -3.f);


//円情報の半径
const float PreparingBlock::SAMPLEBLOCK_COLLIDER_RADIUS = 0.5f;

/*移動処理*/
	//見本ブロックの移動量(X)
const float PreparingBlock::SAMPLEBLOCK_MOVE_VELOCITY_X = MoveSpeed::MOVE_VELOCITY_X;
//見本ブロックの移動量(Y)
const float PreparingBlock::SAMPLEBLOCK_MOVE_VELOCITY_Y = MoveSpeed::MOVE_VELOCITY_Y;
//見本ブロックの移動量(Z)
const float PreparingBlock::SAMPLEBLOCK_MOVE_VELOCITY_Z = MoveSpeed::MOVE_VELOCITY_Z;

//ブロックの拡大率
const DirectX::SimpleMath::Vector3 PreparingBlock::SAMPLEBLOCK_SCALE(1.5f, 1.5f, 0.5f);

//ブロックの初期座標
const DirectX::SimpleMath::Vector3 PreparingBlock::SAMPLEBLOCK_INIT_POSITION(0.0f, 1.3f, -3.0f);

/*===================================
コンストラクタ
引数：なし
===================================*/
PreparingBlock::PreparingBlock()
	: 
	mpSampleModel(nullptr),
	mpCircleCollider(nullptr),
	mMoveFlag(true)
{

	mpSampleModel = std::make_unique<BoxModel>();
	mpCircleCollider = std::make_unique<Circle>();
}

/*===================================
デストラクタ
===================================*/
PreparingBlock::~PreparingBlock()
{
}

/*===================================
初期化
引数：なし
返り値：なし
===================================*/
void PreparingBlock::Initialize()
{

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	//見本ブロック
	auto samplemodel = pRM->GetCmoModel((static_cast<int>(PlayModelsResouce::MODEL__WOODBLOCK)));
	mpSampleModel->SetModel(samplemodel);

	//見本ブロックの情報を設定する
	this->GetBoxModel()->SetPosition(SAMPLEBLOCK_INIT_POSITION);
	this->GetBoxModel()->SetScale(SAMPLEBLOCK_SCALE);


	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpSampleModel->ReturnHalfSize(SAMPLEBLOCK_SCALE);
	//設定
	mpSampleModel->SetAABBCollider(SAMPLEBLOCK_INIT_POSITION - halfsize, SAMPLEBLOCK_INIT_POSITION + halfsize);


	//当たり判定更新処理
	this->CircleColliderUpdate();

}

/*===============================================
更新
引数：移動ベクトル、ライン管理クラスのポインタ
返り値：なし
==================================================*/
void PreparingBlock::Update(
	const DirectX::SimpleMath::Vector3& movevel,
	GridLineManager* pGridLineMnager)
{

	//そもそも移動できない状態なら処理をしない
	if (mMoveFlag)
	{
		//自身の移動処理
		this->Move(movevel, pGridLineMnager);
		/*当たり判定更新*/
		//拡大率の半分の値を生成
		DirectX::SimpleMath::Vector3 halfsize = mpSampleModel->ReturnHalfSize(mpSampleModel->GetScale());
		//設定
		mpSampleModel->SetAABBCollider(mpSampleModel->GetPosition() - halfsize,
			mpSampleModel->GetPosition() + halfsize);

		//当たり判定更新処理
		this->CircleColliderUpdate();
	}
}

/*===================================
描画
引数：なし
返り値：なし
===================================*/
void PreparingBlock::Draw()
{
	mpSampleModel->Draw();
}


/*===================================================
移動処理
引数：移動ベクトル、グリッド線管理クラスのポインタ
返り値：なし
===================================================*/
void PreparingBlock::Move(const DirectX::SimpleMath::Vector3& movevel,
	GridLineManager* pGridLineMnager)
{

	//基本となる座標を算出
	DirectX::SimpleMath::Vector3 basePosition = movevel + BLOCK_SHIFT_PLAYERPOSITION;

	//2D変換
	DirectX::SimpleMath::Vector2 castpos;
	castpos.x = basePosition.x;
	castpos.y = basePosition.z;

	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 subpos;

	//基本となる座標から最も近いグリッド線の交点を取得
	castpos = pGridLineMnager->GetIntersectionNearPosition(castpos);

	subpos.x = castpos.x;
	subpos.y = basePosition.y;
	subpos.z = castpos.y;

	mpSampleModel->SetPosition(subpos);
}




/*===================================================================
建てられないブロック資材変更関数:private
引数：なし
返り値：なし
====================================================================*/
void PreparingBlock::ChangeNotUseBlock()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();

	//表示するブロックを変える
		//見本ブロック
	auto samplemodel = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__NOTUSEDBLOCK));
	this->GetBoxModel()->SetModel(samplemodel);
}

/*==========================================================
資材が足りていないとき処理するブロックの資材変更関数:private
引数：なし
返り値：なし
============================================================*/
void PreparingBlock::ChangeNotEnoughMat()
{
	//所持金を減らす
	auto& pM = Money::GetMoneyInstance();

	//ブロック建て判定取得
	bool Createflag = true;

	if (pM.GetMoney() <= BLOCK_CREATE_MONEY_NUM)
	{
		Createflag = false;
	}

	//もし壁が建てられないなら(資材数が足りない)
	if (!Createflag)
	{
		//建てられない見本モデルに切り替える処理を行う
		this->ChangeNotUseBlock();
	}
}

/*==================
当たり判定生成処理
引数：なし
返り値：なし
====================*/
void PreparingBlock::CircleColliderUpdate()
{		
	//ライン衝突判定用変数の初期化
	//座標変換
	Vector2XZ pos2D;
	pos2D.x = mpSampleModel->GetPosition().x;
	pos2D.z = mpSampleModel->GetPosition().z;
	mpCircleCollider->mCenter = pos2D;
	mpCircleCollider->mRadius = SAMPLEBLOCK_COLLIDER_RADIUS;
}

