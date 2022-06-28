/*
プレイヤーの通常攻撃アニメーションモデルを管理するクラス
作成者：杉山
作成日：2021/09/05
*/
#include"pch.h"

#include"NormalAttackAnim.h"


//定数
//Sin値拡大率
const float NormalAttackAnim::SIN_SCLAE = 3.f;

//アニメーションの速度
const float NormalAttackAnim::ANIM_VELOCITY = 3.5f;
//アニメーションの加速度
const float NormalAttackAnim::ANIM_ACCEL = 1.05f;

//アニメーション最大値
const float NormalAttackAnim::ANIM_MAX_NUM = 180.f;

/*================================
コンストラクタ
引数：なし
================================*/
NormalAttackAnim::NormalAttackAnim()
	:
	mpAnimModel(nullptr),
	mSinNum(0.f),
	mVelocity(0.f),
	mWorld()
{
	mpAnimModel = std::make_unique<ObjectModel>();
}

/*================================
デストラクタ
================================*/
NormalAttackAnim::~NormalAttackAnim()
{
}

/*================================
初期化処理
引数：なし
返り値：なし
================================*/
void NormalAttackAnim::Initialize()
{

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__LANCE));

	mpAnimModel->SetModel(model);

	this->Reset();

	mpAnimModel->SetScale(DirectX::SimpleMath::Vector3::One);

	mVelocity = ANIM_VELOCITY;
}

/*================================
リセット処理
引数：なし
返り値：なし
================================*/
void NormalAttackAnim::Reset()
{
	mVelocity = ANIM_VELOCITY;
	mSinNum = 0.f;
}

/*=============================================================================
更新処理
引数：プレイヤーの攻撃用ワールド座標
返り値：アニメーション稼働フラグ(true:終了)
=============================================================================*/
bool NormalAttackAnim::Update(const DirectX::SimpleMath::Matrix& playerAttackmat)
{

	//値を取得
	float sinf = std::sinf(DirectX::XMConvertToRadians(mSinNum)) * SIN_SCLAE;

	//値を更新する
	mVelocity *= ANIM_ACCEL;
	mSinNum += mVelocity;

	//ワールド座標を計算する
	mWorld = (DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.f, 0.f, -sinf))) * playerAttackmat;
	

	//最大値となったら
	if (mSinNum >= ANIM_MAX_NUM)
	{
		return true;
	}

	return false;
}

/*==============================
描画処理
引数：なし
返り値：なし
================================*/
void NormalAttackAnim::Draw()
{
	//描画
	mpAnimModel->Draw(&mWorld);
}
