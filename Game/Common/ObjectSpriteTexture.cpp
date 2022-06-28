/*
目的の場所にスプライト画像を平面描画するクラス
(スプライト画像はこっち)
作成者：杉山
作成日：2021/06/21
*/
#include "pch.h"
#include "ObjectSpriteTexture.h"

/*=========================================================================
コンストラクタ
引数：src(切り取り座標)、maxsize(画像横幅最大サイズ)、position(描画座標)
		scale(拡大率)、rot(回転率)、alpha(透明度)
=========================================================================*/
ObjectSpriteTexture::ObjectSpriteTexture(const RECT& src,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& scale,
	const float& rot, const float& alpha)
	:
	ITexture(position,scale,rot,alpha),
	mSrc(src),
	mpSpriteBatch(),
	mSpriteSrc()
{
	//サイズ算出
	mSpriteSrc.x = static_cast<float>(src.right - src.left);
	mSpriteSrc.y = static_cast<float>(src.bottom - src.top);
}

/*=========================
デストラクタ
=========================*/
ObjectSpriteTexture::~ObjectSpriteTexture()
{
}

/*=====================================
初期化
引数：なし
返り値：なし
===================================*/
void ObjectSpriteTexture::Initialize()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	//ポインタの保存
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*=========================
描画処理
引数：なし
返り値：なし
=========================*/
void ObjectSpriteTexture::Draw()
{
	//色(透明度の指定)
	DirectX::SimpleMath::Vector4 color{ DirectX::SimpleMath::Vector4::One};
	color.w = ITexture::GetAlpha();
	//中央値の指定
	DirectX::SimpleMath::Vector2 center{ DirectX::SimpleMath::Vector2::Zero };

	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();


	//ポインタの保存
	mpSpriteBatch = pDxIF.GetSpriteBatch();
	//描画
	mpSpriteBatch->Draw
	(
		ITexture::GetTexture(),
		ITexture::GetPosition(),
		&mSrc,
		color,
		ITexture::GetRot(),
		center,
		ITexture::GetScale()
	);

}