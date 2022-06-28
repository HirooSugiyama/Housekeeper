/*
タイマー
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"

#include"Timer.h"

//フレーム最低値
const float Timer::MIN_FRAME = 50.f;

/*===================================
コンストラクタ
引数：なし
===================================*/
Timer::Timer()
	:
	mMaxTime(),
	mMainTimer(),
	mSubTimer()
{
}

/*===================================
デストラクタ
===================================*/
Timer::~Timer()
{
}

/*=================================
更新処理
引数：なし
返り値：終了フラグ
===================================*/
bool Timer::Update()
{
	//現在のFPSを取得
	const auto& pT = TimerComponent::GetTimerInstance();

	float fps = static_cast<float>(pT.GetTimer().GetFramesPerSecond());

	//サブタイマー増加
	mSubTimer += static_cast<float>(pT.GetTimer().GetElapsedSeconds()) * fps;
 
	//大体60FPS==1sなので
	if (mSubTimer >= fps)
	{
		mSubTimer = 0.f;
		mMainTimer++;
	}

	//最大時間となったら
	if (mMainTimer >= mMaxTime)
	{
		return true;
	}

	return false;
}

/*=================================
更新処理
引数：なし
返り値：終了フラグ
===================================*/
bool Timer::ManualUpdate()
{
	//サブタイマー増加
	mSubTimer ++;

	//大体60FPS==1sなので
	if (mSubTimer >= 60.f)
	{
		mSubTimer = 0.f;
		mMainTimer++;
	}

	//最大時間となったら
	if (mMainTimer >= mMaxTime)
	{
		return true;
	}

	return false;
}



