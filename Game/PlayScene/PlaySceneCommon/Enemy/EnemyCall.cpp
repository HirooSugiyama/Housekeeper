/*
敵を読み込むためのクラス
作成者：杉山
作成日：2021/05/25
*/
#include"pch.h"
#include "EnemyCall.h"

/*========================
コンストラクタ
引数：なし
========================*/
EnemyCall::EnemyCall()
	:
	mNormalEnemyInfo(),
	mBossEnemyInfo()
{
}

/*===================================
デストラクタ
===================================*/
EnemyCall::~EnemyCall()
{
}


/*==============================
敵情報を指定する関数
引数：ファイルのパス
返り値：なし
==============================*/
void EnemyCall::LoadInfo(const std::string & filepath)
{
	//ここはチュートリアル専用読み込みクラスなのでファイルから読み込む
	this->SetCSV(filepath);
}

/*=============================
保存用変数を初期化
引数：なし
返り値：なし
==============================*/
void EnemyCall::Reset()
{
	mNormalEnemyInfo.resize(0);
}


/*==============================
ファイル読み込み処理：private
引数：ファイルのパス
返り値：なし
==============================*/
void EnemyCall::SetCSV(const std::string & filepath)
{
	//列挙型を簡素化
	const int csv_position_x = static_cast<int>(eEnemyCSV::POSITION_X);
	const int csv_position_y = static_cast<int>(eEnemyCSV::POSITION_Y);
	const int csv_position_z = static_cast<int>(eEnemyCSV::POSITION_Z);
	const int phasenum = static_cast<int>(eEnemyCSV::PHASE_NUM);
	const int enemyType = static_cast<int>(eEnemyCSV::ENEMY_TYPE);

	//例外処理
	Utility::FileError(filepath);

	//ファイル変換
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;
	//一時的に保存用
	EnemyInfo instantPosition;

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
			//座標の保存
			if (j == csv_position_x) {
				instantPosition.mVectorESPosition.x = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_position_y) {
				instantPosition.mVectorESPosition.y = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_position_z) {
				instantPosition.mVectorESPosition.z = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == phasenum) {
				instantPosition.mPhaseNumber = static_cast<int>(atoi(tileBuf.c_str()));
			}
			else if (j == enemyType) {
				instantPosition.mType = static_cast<EnemyType>(atoi(tileBuf.c_str()));
			}
		}

		if (instantPosition.mPhaseNumber != 0)
		{
			//種類によって処理を変える
			switch (instantPosition.mType)
			{
				case EnemyType::NORMAL:
				{
					//サイズを増やす
					mNormalEnemyInfo.push_back(instantPosition);

					break;
				}
				case EnemyType::BOSS:
				{
					mBossEnemyInfo = instantPosition;
					break;
				}
				default:
				{
					throw "Exception handling";
					break;
				}
			}
			instantPosition.mPhaseNumber = 0;
			instantPosition.mVectorESPosition = DirectX::SimpleMath::Vector3::Zero;
		}		
	}
}