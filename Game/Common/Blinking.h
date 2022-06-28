/*
点滅処理クラス
作成者：杉山
作成日：2021/11/01
*/
#pragma once

class Blinking
{
private:

	//点滅フラグ
	bool mBlinkingFlag;
	//sin値
	float mSinfNum;
	//点滅間隔
	float mBlinkingInterval;
	//計測値
	float mBlinkingNum;

public:

	//コンストラクタ
	Blinking(float intervalNum = 0.1f);
	//デストラクタ
	~Blinking();
	//更新処理
	void Update();

	//フラグのアクセサ
	bool GetBlinkingFlag()const { return mBlinkingFlag; }
};
