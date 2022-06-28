/*
スコア管理クラス
作成者：杉山
作成日：2021/06/28
*/
#pragma once


class Score
{
private:

	//スコア数
	int mScore;

public:
	//コンストラクタ
	Score()
		:mScore(0)
	{};
	//デストラクタ
	~Score()
	{
	};

	//ゲージ数のアクセサ
	int GetScoreNum()const { return mScore; }
	void SetScoreInit(const int& overwrite) { mScore = overwrite; }
	void SetScoreUp(const int& upnum) { mScore += upnum; }
	void SetScoreDown(const int& downnum) { mScore -= downnum; }

};
