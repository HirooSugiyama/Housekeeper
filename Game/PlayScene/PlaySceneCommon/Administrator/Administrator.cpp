/*
管理者クラス～HPやタイマーを持つ～
作成者：杉山
作成日：2021/05/25
*/

#include"pch.h"
#include "Administrator.h"

//資材所持数描画位置
const DirectX::SimpleMath::Vector2 Administrator::COUNTER_DROW_POSITION(1000.f, 190.f);

//表示一ずらし用変数
const int Administrator::SHIFT_POSITION_NUM = 100;

/*===================================
コンストラクタ
引数：なし
===================================*/
Administrator::Administrator()
	:
	mpAdTimer(nullptr),
	mpCelestialSphere(nullptr),
	mpScore(nullptr),
	mPhaseNum(0),
	mUsePriceNum(0),
	mClearBonusScoreNum(0)
{
	mpAdTimer = std::make_unique<Timer>();

	mpCelestialSphere = std::make_unique <CelestialSphere>();
	mpScore = std::make_unique <Score>();

}

/*===================================
デストラクタ
===================================*/
Administrator::~Administrator()
{
}

/*===================================
初期化
引数：なし
返り値：なし
===================================*/
void Administrator::Initialize()
{
	mpCelestialSphere->Initialize();
}

/*===================================
更新
引数：なし
返り値：なし
===================================*/
void Administrator::Update()
{
	mpAdTimer->Update();
}

/*==================================
ファイルから情報を取得
引数：ファイル名
返り値：なし
===================================*/
void Administrator::LoadCSV(const std::string& filename)
{
	//例外処理
	Utility::FileError(filename);

	//ファイル変換
	std::ifstream ifs(filename);
	//1行の情報を保存する変数
	std::string lineBuf;

	//1行の読み込み処理_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			switch (j)
			{
				//防衛時間を取得
				case DEFENCE_TIME:
				{
					int consttimer = atoi(tileBuf.c_str());
					mpAdTimer->SetMaxTime(consttimer);
					break;
				}
				//フェーズ数を取得
				case PHASE_NUM:	
				{
					mPhaseNum = atoi(tileBuf.c_str());
					break;
				}
				//使用可能金額を取得
				case PRICE:
				{
					mUsePriceNum = atoi(tileBuf.c_str());
					break;
				}	
				//クリア時のボーナススコアを取得
				case CLEAR_BONUS:
				{
					mClearBonusScoreNum = atoi(tileBuf.c_str());
					break;
				}
			}
		}
	}
}
