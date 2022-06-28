/*
動く数字
作成者：杉山
作成日：2021/10/13
*/
#pragma once





namespace DX
{
	class StepTimer;
}

class CountNumber
{
private:

	//初期値
	float mFirstNum;

	//最大値(向かう数)
	int mTopNum;

	//増加量
	float mVelocityNum;

	//1秒当たりの増加量
	float mOneSecondVelocityNum;


public:

	//コンストラクタ
	CountNumber();
	//デストラクタ
	~CountNumber();
	//初期化処理
	void Initialize(int firstNum, float moveSecondSpeed, int maxNum);
	//更新処理
	int Update(const DX::StepTimer& timer,bool fallflag=false);

	//現在の数値のアクセサ
	int GetMoveNum() const { return static_cast<int>(mFirstNum); }

	//指定の値に強制変更
	void ForcedChangeMoveNum() { mFirstNum = static_cast<float>(mTopNum); }

};
