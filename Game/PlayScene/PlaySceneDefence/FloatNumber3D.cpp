/*
数字が浮く表現を行うクラス
作成者：杉山
作成日：2021/10/22
*/
#include"pch.h"

#include"FloatNumber3D.h"

//前方宣言
#include"../../Common/ObjectSpriteTexture.h"
#include"../Effect/Effect.h"
#include"Libraries/MyLibraries/CameraBase.h"

//数字同士の幅
const float FloatNumber3D::NUM_SHIFT = 0.9f;

//数字の移動速度
const float FloatNumber3D::NUM_MOVE_VELOCITY = 0.05f;


//透明度の変化速度
const float FloatNumber3D::NUM_ALPHA_VELOCITY = 0.03f;

//画像拡大率
const DirectX::SimpleMath::Vector2 FloatNumber3D::TEX_SCALE(0.5f, 1.f);

/*==================================
コンストラクタ
引数：なし
===================================*/
FloatNumber3D::FloatNumber3D()
	:
	NumberBase(),
	mpNumberTexture(),
	mpCamera(),
	mInitPosition(),
	mUseFlag(false)
{
	//画像の準備
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i] = std::make_unique<EffectSpriteTexture>
			(
				1,											//画像初期行数		
				DirectX::SimpleMath::Vector3::Zero,			//座標
				TEX_SCALE									//拡大率
			);
	}
}

/*===================================
デストラクタ
===================================*/
FloatNumber3D::~FloatNumber3D()
{
}

/*===================================
初期化処理
引数：カメラのポインタ
返り値：なし
===================================*/
void FloatNumber3D::Initialize(CameraBase* pCamera)
{
	//リソースの取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWDAMAGESTRING));

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetTexture(texture);
		mpNumberTexture[i]->Initialize();
		mpNumberTexture[i]->SetHorizontalCutNum(10);		//横幅[固定]
		mpNumberTexture[i]->SetCameraEyePosition(pCamera->GetEyePosition());
		mpNumberTexture[i]->SetWidthNum(Utility::EXCEPTION_NUM);				//例外数字
	}	
}

/*==================================
作成処理
引数：表示する数字、表示する座標
返り値：なし
===================================*/
void FloatNumber3D::Create(int num, DirectX::SimpleMath::Vector3 position)
{
	mInitPosition = position;

	//各種数字を保存する//必要な数字を選び出す
	this->CreateNumber(NumberBase::ChooseNum(num));

	//座標を設定する
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//例外数字なら描画する
		if (mpNumberTexture[i]->GetWidthNum() != Utility::EXCEPTION_NUM)
		{
			mpNumberTexture[i]->SetPosition(mInitPosition+ DirectX::SimpleMath::Vector3((i*NUM_SHIFT),0.f,0.f));
		}
	}

	//使用状態とする
	mUseFlag = true;
}

/*=================================
更新処理
引数：なし
返り値：なし
===================================*/
void FloatNumber3D::Update()
{	
	//使用していなかったら処理をしない
	if (!mUseFlag)return;

	DirectX::SimpleMath::Vector3 movepos = DirectX::SimpleMath::Vector3::Zero;

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//例外数字なら描画する
		if (mpNumberTexture[i]->GetWidthNum() != Utility::EXCEPTION_NUM)
		{
			//移動処理
			movepos = mpNumberTexture[i]->GetPosition();
			movepos.y += NUM_MOVE_VELOCITY;
			mpNumberTexture[i]->SetPosition(movepos);

			//透明化処理
			mpNumberTexture[i]->SetAlpha(NumberBase::GetTextureAlpha());
		}
	}

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//例外数字以外なら描画する
		if (mpNumberTexture[i]->GetWidthNum() != Utility::EXCEPTION_NUM)
		{
			NumberBase::SetTextureAlpha(NumberBase::GetTextureAlpha() - NUM_ALPHA_VELOCITY);

			NumberBase::SetTextureAlpha(NumberBase::GetTextureAlpha()-NUM_ALPHA_VELOCITY);

			//もし完全に透明になったら
			if (NumberBase::GetTextureAlpha() <= 0.0f)
			{
				//リセット処理を通す
				this->Reset();
			}

			break;
		}
	}
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void FloatNumber3D::Draw()
{
	//使用していなかったら処理をしない
	if (!mUseFlag)return;

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//例外数字なら描画する
		if (mpNumberTexture[i]->GetWidthNum()!= Utility::EXCEPTION_NUM)
		{
			mpNumberTexture[i]->ExtendDraw();
		}
	}	
}


/*===============================================
リセット処理
引数：なし
返り値：なし
===============================================*/
void FloatNumber3D::Reset()
{
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetWidthNum(Utility::EXCEPTION_NUM);				//例外数字で初期化
		mpNumberTexture[i]->SetAlpha(NumberBase::GetInitAlpha());			//透明度を元に戻す
	}
	NumberBase::SetTextureAlpha(NumberBase::GetInitAlpha());

	//使用していなかったら処理をしない
	mUseFlag = false;
}


/*===============================================
各変数にほしい番号を入れる:private
引数：作成する数字群
返り値：なし
=================================================*/
void FloatNumber3D::CreateNumber(std::vector<int> num)
{
	//-1で初期化

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetWidthNum(Utility::EXCEPTION_NUM);				//例外数字
	}


	for (int i = 0; i < static_cast<int>(num.size()); i++)
	{
		mpNumberTexture[i]->SetWidthNum(num[i]);
	}
}
