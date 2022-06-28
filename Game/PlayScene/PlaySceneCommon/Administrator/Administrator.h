/*
管理者クラス～HPやタイマーを持つ～
作成者：杉山
作成日：2021/05/25
*/
#pragma once


//所持
#include"CelestialSphere.h"
#include"Score.h"
#include"Timer.h"

enum AdCSV
{
	DEFENCE_TIME,		//準備時間
	PHASE_NUM,			//フェーズ数
	PRICE,				//使用可能金額
	CLEAR_BONUS,		//クリア時のボーナススコア
};


class Administrator
{
private:

	//定数

	//資材所持数描画位置
	static const DirectX::SimpleMath::Vector2 COUNTER_DROW_POSITION;
	//表示一ずらし用変数
	static const int SHIFT_POSITION_NUM;

	//タイマー
	std::unique_ptr<Timer> mpAdTimer;

	//天球
	std::unique_ptr<CelestialSphere> mpCelestialSphere;

	//スコア
	std::unique_ptr<Score> mpScore;

	//フェーズ数
	int mPhaseNum;

	//使用可能金額
	int mUsePriceNum;

	//クリア時のボーナススコア
	int mClearBonusScoreNum;

public:
	//コンストラクタ
	Administrator();
	//デストラクタ
	~Administrator();
	//初期化
	void Initialize();
	//更新
	void Update();

	//タイマーに直接アクセスする
	Timer* DirectAcceserTimer() const { return mpAdTimer.get(); }


	//天球へ直接アクセスする
	CelestialSphere* DirectAcceserCelestialSphere() const { return mpCelestialSphere.get(); }


	//スコアへ直接アクセスする
	Score* DirectAcceserScore() const { return mpScore.get(); }


	//ファイル読み込み
	void LoadCSV(const std::string& filename);

	//Phase数の取得
	int GetPhaseNum()const { return mPhaseNum; }

	//使用可能金額の取得
	int GetUsePriceNum()const { return mUsePriceNum; }


	//クリア時のボーナススコアの取得
	int GetClearBonusScoreNum() const { return mClearBonusScoreNum; }
};
