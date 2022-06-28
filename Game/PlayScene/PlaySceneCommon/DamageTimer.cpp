/*
ダメージ計測タイマークラス
作成者：杉山
作成日：2021/06/16
*/

#include "pch.h"
#include "DamageTimer.h"

const int DamageTimer::DAMAGE_TIMER = 3;

/*==============================
コンストラクタ
引数：なし
==============================*/
DamageTimer::DamageTimer()
	:
	mMainTimer(0),
	mSubTimer(0),
	mIntervalTimer(0),
	mIntervalFlag(false)
{
}

/*==============================
デストラクタ
==============================*/
DamageTimer::~DamageTimer()
{
}
/*==============================
更新処理
引数：なし
返り値：タイマー終了フラグ
==============================*/
bool DamageTimer::Update()
{
	//タイマーの取得
	const auto& pT = TimerComponent::GetTimerInstance();
	
	mSubTimer++;
	mIntervalTimer++;
	if (mSubTimer >= static_cast<int>(pT.GetTimer().GetFramesPerSecond())) 
	{
		mSubTimer = 0;
		mMainTimer++;
	}
	//時間になったらtrueを返す。
	if (mMainTimer == DAMAGE_TIMER) 
	{
		mMainTimer = 0;
		mIntervalTimer = 0;
		return true;
	}
	return false;
}


/*==============================
一定間隔でフラグを返す処理
引数：時間
返り値：表示フラグ(true→表示)
==============================*/
int DamageTimer::RegularIntervalTimer(const int& interval)
{
	//一定時間になったら
	if (mIntervalTimer == interval) 
	{		
		//表示されていたら
		if (mIntervalFlag) 
		{
			//非表示にする
			mIntervalFlag = false;
		}
		//非表示なら
		else 
		{
			//表示する
			mIntervalFlag = true;
		}
		mIntervalTimer = 0;
	}
	
	return mIntervalFlag;
}
