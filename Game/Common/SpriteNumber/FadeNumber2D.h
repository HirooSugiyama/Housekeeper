/*
フェード処理を行う数字画像のクラス
作成者：杉山
作成日：2021/12/11
*/
#pragma once

#include"SpriteNumber2D.h"


class FadeNumber2D :public SpriteNumber2D
{
private:

public:

	//コンストラクタ
	FadeNumber2D();
	//デストラクタ
	~FadeNumber2D()override;

	//更新処理
	void Update()override;

	//リセット処理
	void Reset();

};
