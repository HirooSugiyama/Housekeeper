/*
目的の場所に画像を平面描画するクラス
(単一画像はこっち)
作成者：杉山
作成日：2021/06/05
*/
#include "pch.h"
#include "ObjectTexture.h"

/*=======================================
コンストラクタ
引数：	position(座標)、scale(拡大率)
		rot(回転率)、alpha(透明度)
=======================================*/
ObjectTexture::ObjectTexture(
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const float& rot, const float& alpha)
	:
	ITexture(position, scale,rot,alpha),
	mColor{ DirectX::SimpleMath::Vector4::One},
	mpSpriteBatch(nullptr)
{
	mColor.w = ITexture::GetAlpha();
}

/*=========================
デストラクタ
=========================*/
ObjectTexture::~ObjectTexture()
{
}

/*=========================
初期化
引数：なし
返り値：なし
=========================*/
void ObjectTexture::Initialize()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	
	//ポインタの保存
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*========================
描画
引数：なし
返り値：なし
=========================*/
void ObjectTexture::Draw()
{
	//α値を設定する
	mColor.w = ITexture::GetAlpha();

	//描画
	mpSpriteBatch->Draw(ITexture::GetTexture(),
		ITexture::GetPosition(),
		nullptr,
		mColor,
		ITexture::GetRot(),
		DirectX::SimpleMath::Vector2::One,
		ITexture::GetScale());
}
