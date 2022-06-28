/*
ダメージ計測タイマークラス
作成者：杉山
作成日：2021/06/16
*/
#pragma once




class DamageTimer
{
private:
	//定数
	//PSceneState変更時間
	static const int DAMAGE_TIMER;

	//変数
		//タイマー
	int mMainTimer;
	int mSubTimer;
	int mIntervalTimer;
		//一定間隔で変わるフラグ
	bool mIntervalFlag;

public:
	//関数
	//コンストラクタ
	DamageTimer();
	//デストラクタ
	~DamageTimer();
	//更新処理
	bool Update();

	//一定間隔でtrueを返す処理
	int RegularIntervalTimer(const int& interval);
};