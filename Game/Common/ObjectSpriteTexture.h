/*
目的の場所に画像を平面描画するクラス
(スプライト画像はこっち)
作成者：杉山
作成日：2021/06/21
*/
#pragma once

//基底クラス
#include"ITexture.h"

namespace DirectX
{
	class SpriteBatch;
}
class ObjectSpriteTexture:public ITexture
{
private:
	//変数============================

	//切り取り座標
	RECT mSrc;

	//保存用スプライトバッチ
	DirectX::SpriteBatch* mpSpriteBatch;

	//スプライト切り取り単位
	DirectX::SimpleMath::Vector2 mSpriteSrc;

	//関数============================

public:
	//コンストラクタ
	ObjectSpriteTexture(const RECT& src = {0,0,0,0},					//切り取り座標
		const DirectX::SimpleMath::Vector2& position = { 0.f,0.f },			//表示座標						
		const DirectX::SimpleMath::Vector2& scale = { 1.f,1.f },		//表示拡大率											
		const float& rot = 0.f,										//回転					
		const float& alpha = 1.f);										//透明度	
										


	//デストラクタ
	~ObjectSpriteTexture();

	//初期化
	void Initialize()override;

	//描画
	void Draw()override;

	//切り取り位置変更処理
	void SetRect(const RECT& rect) { mSrc = rect; }

	//指定の幅だけ横に画像を移動させる
	void Beside(const float& size,const int& shiftnum)
	{
		mSrc.right += static_cast<LONG>(size* shiftnum);
		mSrc.left += static_cast<LONG>(size * shiftnum);
	}
};