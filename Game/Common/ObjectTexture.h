/*
目的の場所に画像を平面描画するクラス
(単一画像はこっち)
作成者：杉山
作成日：2021/06/05
*/
#pragma once

//基底クラス
#include"ITexture.h"

namespace DirectX
{
	class SpriteBatch;
}
class ObjectTexture:public ITexture
{
private:
	//変数============================
	
	DirectX::SimpleMath::Vector4 mColor;

	//保存用スプライトバッチ
	DirectX::SpriteBatch* mpSpriteBatch;

	//関数============================

public:
	//コンストラクタ
	ObjectTexture(const DirectX::SimpleMath::Vector2& position = { 0.f,0.f },
					const DirectX::SimpleMath::Vector2& scale = { 1.f,1.f },
					const float& rot = 0.f, const float& alpha = 1.f);
	//デストラクタ
	~ObjectTexture();


	//初期化
	void Initialize()override;
	//描画
	void Draw()override;

};