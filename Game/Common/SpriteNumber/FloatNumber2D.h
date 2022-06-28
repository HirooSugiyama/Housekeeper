/*
数字が浮く表現を行うクラス
作成者：杉山
作成日：2021/10/22
*/
#pragma once

//基底クラス
#include"SpriteNumber2D.h"


class FloatNumber2D :public SpriteNumber2D
{
private:

	//透明度の変化速度
	static const float NUM_ALPHA_VELOCITY;

	//数字の移動速度
	static const float NUM_MOVE_VELOCITY;

	//画像拡大率
	static const DirectX::SimpleMath::Vector2 FLOAT_TEX_SCALE;

public:

	//コンストラクタ
	FloatNumber2D();
	//デストラクタ
	~FloatNumber2D()override;
	//更新処理
	void Update()override;

	//リセット処理
	void Reset();
};

