/*
動く数字
作成者：杉山
作成日：2021/10/13
*/
#include"pch.h"

#include"CountNumber.h"

#include"StepTimer.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
CountNumber::CountNumber()
	:
	mFirstNum(),
	mVelocityNum(),
	mTopNum(),
	mOneSecondVelocityNum()
{
}

/*===================================
デストラクタ
===================================*/
CountNumber::~CountNumber()
{
}

/*===================================================================================
初期化処理
引数：firstNum(最初の値)、moveSecondSpeed(増加する時間)、maxNum(最初の値の最大値)
返り値：なし
===================================================================================*/
void CountNumber::Initialize(int firstNum, float moveSecondSpeed, int maxNum)
{
	//引数を保存する
	mFirstNum = static_cast<float>(firstNum);
	mTopNum = maxNum;


	//1秒当たりの増加量を計算する
	float movenum = static_cast<float>(mTopNum) - mFirstNum;//増加しなければならない値を算出
	mOneSecondVelocityNum = movenum / moveSecondSpeed;			//秒数で割る
}

/*================================================================
更新処理
引数：	timer(標準のタイマー)
		fallflag(減少フラグ。trueの時は値を減らす[default:false])
返り値：変更後の値
==================================================================*/
int CountNumber::Update(const DX::StepTimer& timer, bool fallflag)
{
	unsigned int fps = timer.GetFramesPerSecond();

	//割る0回避
	if (fps == 0)
	{
		fps++;
	}

	//1F当たりの増加量を計算する
	mVelocityNum = mOneSecondVelocityNum / fps;



	//値を増やすか減らすかで処理を変える
	switch (fallflag)
	{
		case true:
		{
			//最小値に到達していなければ
			if (mFirstNum > mTopNum)
			{
				//徐々に減らしていく
				mFirstNum += mVelocityNum;
			}
			//最小値以上になったら補正する
			if (mFirstNum < mTopNum)
			{
				mFirstNum = static_cast<float>(mTopNum);
			}

			break;
		}
		case false:
		{
			//最大値に到達していなければ
			if (mFirstNum < mTopNum)
			{
				//徐々に足していく
				mFirstNum += mVelocityNum;
			}
			//最大値以上になったら補正する
			if (mFirstNum > mTopNum)
			{
				mFirstNum = static_cast<float>(mTopNum);
			}

			break;
		}
	}
	return static_cast<int>(mFirstNum);
}
