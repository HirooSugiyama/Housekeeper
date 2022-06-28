/*
画像管理クラスのインターフェースクラス
作成者：杉山
作成日：2021/12/01
*/

#include"pch.h"
#include"ITexture.h"

/*===============================================
コンストラクタ
引数：座標、拡大率、回転率、透明度
===============================================*/
ITexture::ITexture(const DirectX::SimpleMath::Vector2& position,
				const DirectX::SimpleMath::Vector2& scale,
				const float& rot, const float& alpha)
	:
	mPosition(position),
	mScale(scale),
	mRot(rot),
	mAlpha(alpha),
	mTexture(nullptr),
	mInputLayout(nullptr)
{
}
