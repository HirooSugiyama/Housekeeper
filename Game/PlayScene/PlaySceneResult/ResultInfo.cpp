/*
リザルトで使用する情報を読み込み、管理するクラス
作成者：杉山
作成日：2021/10/23
*/
#include"pch.h"

#include"ResultInfo.h"


/*===================================
コンストラクタ
引数：なし
===================================*/
ResultInfo::ResultInfo()
	:
	mScoreRanking{},
	mFilePath("none")
{
}

/*===================================
デストラクタ
===================================*/
ResultInfo::~ResultInfo()
{
}

/*===================================
初期化処理
引数：ステージ番号
返り値：なし
===================================*/
void ResultInfo::Initialize(const int& stagenum)
{
	//ファイル名作成
	std::string filetop = "SaveData/Stage",
		filebottom = "Score.csv";

	mFilePath = filetop + std::to_string(stagenum) + filebottom;

	
	//ファイル読み込み
	this->LoadScoreRanking();


}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void ResultInfo::Update()
{

}

/*==================================
スコアランキング読み込み
引数：なし
返り値：なし
===================================*/
void ResultInfo::LoadScoreRanking()
{
	//例外処理
	Utility::FileError(mFilePath);

	//ファイル変換
	std::ifstream ifs(mFilePath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//スコアランキングのスコアを保存
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		std::getline(ifs, lineBuf);
		//スコアを保存
		mScoreRanking[i] = atoi(lineBuf.c_str());
	}
}

/*==================================
スコアランキング読み込み
引数：スコア値
返り値：なし
===================================*/
void ResultInfo::SetScoreRanking(const int& scorenum)
{
	//管理用変数の宣言
	int instantScoreRanking[ResultDrawStringConstant::SCORE_RANKING_STORAGE]{0,0,0,0,0};
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		instantScoreRanking[i] = mScoreRanking[i];
	}

	int j = 0;
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++,j++)
	{
		//もし取得したスコアのほうが高かったら
		if (instantScoreRanking[i] < scorenum&&i==j)
		{
			mScoreRanking[i] = scorenum;
			j--;
		}
		else
		{
			mScoreRanking[i] = instantScoreRanking[j];
		}

	}
}

/*==================================
スコアを書き込む
引数：なし
返り値：なし
===================================*/
void ResultInfo::WriteScore()
{
	//現在の金額をファイルに保存する
	std::ofstream writingFile;
	writingFile.open(mFilePath, std::ios::out);


	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		writingFile << mScoreRanking[i] << std::endl;
	}

	writingFile.close();

}