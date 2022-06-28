/*
タイマー
作成者：杉山
作成日：2021/10/21
*/
#pragma once

class Timer
{
private:

	//フレーム最低値
	static const float MIN_FRAME;

	//最大時間
	int mMaxTime;

	//タイマー
	float mMainTimer;
	float mSubTimer;

public:

	//コンストラクタ
	Timer();
	//デストラクタ
	~Timer();
	//更新処理
	bool Update();
	bool ManualUpdate();


	//最大時間のアクセサ
	void SetMaxTime(const int& time) { mMaxTime = time; }
	int GetMaxTime()const { return mMaxTime; }

	//現在の時間のアクセサ
	int GetMainTimer()const { return static_cast<int>(mMainTimer); }

	//現在の時間をリセットする
	void ResetMainTimer() { mMainTimer = 0; }
};
