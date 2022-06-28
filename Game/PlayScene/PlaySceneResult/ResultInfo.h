/*
リザルトで使用する情報を読み込み、管理するクラス
作成者：杉山
作成日：2021/10/23
*/
#pragma once

//定数の使用
#include"ResultDrawStringConstant.h"

class ResultInfo
{
private:

	//スコアランキング管理用変数
	int mScoreRanking[ResultDrawStringConstant::SCORE_RANKING_STORAGE];

	//読み込むファイルのパス
	std::string mFilePath;

public:

	//コンストラクタ
	ResultInfo();
	//デストラクタ
	~ResultInfo();
	//初期化処理
	void Initialize(const int& stagenum);
	//更新処理
	void Update();

	//スコアランキング読み込み
	void LoadScoreRanking();

	//スコアをランキングに入れる
	void SetScoreRanking(const int& scorenum);


	//スコアを書き込む
	void WriteScore();

	//スコアの取得
	int GetScoreRanking(const int& i)const { return mScoreRanking[i]; }
};
