/*
数字が浮く表現を行うクラス
作成者：杉山
作成日：2021/10/22
*/
#include"pch.h"

#include"FloatNumber2D.h"

//前方宣言
#include"../../Common/ObjectSpriteTexture.h"
#include"Libraries/MyLibraries/CameraBase.h"

//透明度の変化速度
const float FloatNumber2D::NUM_ALPHA_VELOCITY = 0.06f;

//数字の移動速度
const float FloatNumber2D::NUM_MOVE_VELOCITY = 9.f;

//画像拡大率
const DirectX::SimpleMath::Vector2 FloatNumber2D::FLOAT_TEX_SCALE(0.25f, 0.25f);

/*==================================
コンストラクタ
引数：なし
===================================*/
FloatNumber2D::FloatNumber2D()
	:
	SpriteNumber2D()
{
	//画像の準備
	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		SpriteNumber2D::GetNumberTexture(i)->SetScale(FLOAT_TEX_SCALE);
	}
}

/*===================================
デストラクタ
===================================*/
FloatNumber2D::~FloatNumber2D()
{
}


/*=================================
更新処理
引数：なし
返り値：なし
===================================*/
void FloatNumber2D::Update()
{
	DirectX::SimpleMath::Vector2 movePosition(DirectX::SimpleMath::Vector2::Zero);

	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//例外数字以外なら描画する
		if (SpriteNumber2D::GetUseFlag(i))
		{
			//移動処理
			movePosition = SpriteNumber2D::GetNumberTexture(i)->GetPosition();
			movePosition.y -= NUM_MOVE_VELOCITY;
			SpriteNumber2D::GetNumberTexture(i)->SetPosition(movePosition);
		}
	}
	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//例外数字以外なら描画する
		if (SpriteNumber2D::GetUseFlag(i))
		{
			NumberBase::SetTextureAlpha(NumberBase::GetTextureAlpha()- NUM_ALPHA_VELOCITY);
			break;
		}
	}

	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//例外数字以外なら描画する
		if (SpriteNumber2D::GetUseFlag(i))
		{
			//透明化処理
			SpriteNumber2D::GetNumberTexture(i)->SetAlpha(NumberBase::GetTextureAlpha());

			//もし完全に透明になったら
			if (NumberBase::GetTextureAlpha() <= 0.0f)
			{
				//リセット処理を通す
				this->Reset();
			}
		}
	}
}


/*===============================================
リセット処理
引数：なし
返り値：なし
===============================================*/
void FloatNumber2D::Reset()
{
	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//未使用処理
		SpriteNumber2D::SetUseFlag(i,false);
		SpriteNumber2D::GetNumberTexture(i)->SetAlpha(1.f);								//透明度を元に戻す
		SpriteNumber2D::GetNumberTexture(i)->SetRect(SpriteNumber2D::GetSpriteSize());	//UV座標を元に戻す
	}
	//初期化
	NumberBase::SetTextureAlpha(1.f);
}