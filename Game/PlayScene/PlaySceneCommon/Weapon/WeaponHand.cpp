/*
弱攻撃クラス
作成者：杉山
作成日：2021/09/14
*/
#include"pch.h"
#include"WeaponHand.h"

//関数の使用
#include"../ObjectModel/BoxModel.h"


//プレイヤーの座標から攻撃判定までの距離
const DirectX::SimpleMath::Vector3 WeaponHand::ATTACKSTATE_PLAYER_DISTANCE_POSITION(0.f, 0.f,-3.5f);

//当たり判定の拡大率
//モデル
const DirectX::SimpleMath::Vector3 WeaponHand::ATTACKSTATE_COLLIRDEMODEL_SCALE(3.5f, 1.f, 1.f);

const float WeaponHand::ATTACKSTATE_COLLIRDE_SCALE = 1.6f;


//攻撃最大フレーム数
const int WeaponHand::ATTACKSTATE_MAX_ATTACK_FRAME = 60;
//反動最大フレーム数
const int WeaponHand::ATTACKSTATE_MAX_RECOIL_FRAME = 5;

//敵への1回の攻撃のダメージ値
const int WeaponHand::ATTACKSTATE_HAND_DAMAGE = 2;

//アニメーションの座標を少し上げる値
const float WeaponHand::ATTACK_STATE_SHIFT_ANIMATION = 1.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
WeaponHand::WeaponHand()
	:
	mpWeapon(nullptr),
	mpAnim(nullptr),
	mpPlayer(nullptr),
	mWorld(),
	mAttackFlag(eHandState::STAND_BY),
	mAttackFrameCountNum(0),
	mAnimationFlag(false),
	mColliderPosition(DirectX::SimpleMath::Vector3::Zero)
{
	mpWeapon = std::make_unique<SphereModel>();
	mpAnim = std::make_unique<NormalAttackAnim>();
}

/*===================================
デストラクタ
===================================*/
WeaponHand::~WeaponHand()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WeaponHand::Initialize()
{

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();

	//拡大率の設定
	mpWeapon->SetScale(ATTACKSTATE_COLLIRDEMODEL_SCALE);

	//座標の更新は更新処理で

	//アニメーションの初期化処理
	mpAnim->Initialize();
}

/*=======================================================================
更新処理
引数：なし
返り値：なし
=======================================================================*/
void WeaponHand::Update()
{
	//代入用変数の準備
	DirectX::SimpleMath::Vector3 position;
	position = mpPlayer->GetPlayerModel()->GetPosition() + ATTACKSTATE_PLAYER_DISTANCE_POSITION;

	//座標の設定
	mpWeapon->SetPosition(position);

	//簡略化変数の宣言
	DirectX::SimpleMath::Matrix trans;

	trans = DirectX::SimpleMath::Matrix::CreateTranslation(ATTACKSTATE_PLAYER_DISTANCE_POSITION);

	//計算する(描画処理で使用)
	mWorld = trans * mpPlayer->GetPlayerAttackWorldMatrix();

	//攻撃フレーム計測処理
	this->AttackFrameCount();

	//攻撃状態なら処理を通す
	if (mAttackFlag==eHandState::ATTACK&&!mAnimationFlag)
	{
		//当たり判定作成
		this->SetCollider();


		//アニメーションの更新処理
		mAnimationFlag = mpAnim->Update(mpPlayer->GetPlayerAttackWorldMatrix());
	}
	//非攻撃状態なら異なる処理を通す
	else 
	{
		mpWeapon->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);
	}


	//現在の反動フレームが最大に到達したら
	if (mAnimationFlag &&mAttackFrameCountNum < -ATTACKSTATE_MAX_RECOIL_FRAME)
	{
		//非攻撃状態とし
		mAttackFlag = eHandState::STAND_BY;

		//リセット処理を行う
		this->Reset();
	}
}


/*=================================
描画処理
引数：なし
返り値：なし
===================================*/
void WeaponHand::Draw()
{
	//攻撃状態なら処理を通す
	if (mAttackFlag== eHandState::ATTACK)
	{
		//アニメーションの描画処理
		mpAnim->Draw();
	}
}

/*=========================================
当たり判定の作成:private
引数:生成フラグ(false 作成しない)
返り値：なし
=========================================*/
void WeaponHand::SetCollider(const bool& flag)
{
	switch (flag)
	{
		case false:
		{
			/*当たり判定生成*/
			mColliderPosition =
				DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Zero, mWorld);
			mpWeapon->SetSphereCollider(mColliderPosition, ATTACKSTATE_COLLIRDE_SCALE);
			break;
		}
		case true:
		{
			/*当たり判定削除*/
			mpWeapon->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);

			break;
		}

	}
}

/*===========================
攻撃判定稼働時間:private
引数：なし
返り値：なし
===========================*/
void WeaponHand::AttackFrameCount()
{

	//現在の攻撃フレームが最大フレームに到達したら
	if (mAnimationFlag&& mAttackFlag== eHandState::ATTACK)
	{
		//反動状態とし
		mAttackFlag = eHandState::COOL_TIME;	
	}


	if (mAttackFlag == eHandState::COOL_TIME)
	{
		mAttackFrameCountNum--;//攻撃フレームを増やしていく
	}
}

/*===========================
リセット処理:private
引数：なし
返り値：なし
===========================*/
void WeaponHand::Reset()
{
	mAttackFrameCountNum = 0;//カウントをリセットする	
	mAnimationFlag = false;

	//アニメーションのリセット処理
	mpAnim->Reset();

}
