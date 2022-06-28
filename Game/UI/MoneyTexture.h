/*
所持金周りの描画画像管理クラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once


//前方宣言
#include"../Common/ObjectTexture.h"
#include"../Common/SpriteNumber/SpriteNumber2D.h"

class MoneyTexture
{
private:

	//画像の座標
	static const DirectX::SimpleMath::Vector2 UI_MONEYTEXTURE_POSITION;
	//画像の拡大率
	static const DirectX::SimpleMath::Vector2 UI_MONEYTEXTURE_SCALE;
	//実際の値の描画
	static const DirectX::SimpleMath::Vector2 UI_MONEY_NUM_POSITION;

	//ユニークポインタ
	std::unique_ptr<ObjectTexture> mpTexture;
	std::unique_ptr<SpriteNumber2D> mpSpriteTexture;

public:

	//コンストラクタ
	MoneyTexture();
	//デストラクタ
	~MoneyTexture();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw();

};
