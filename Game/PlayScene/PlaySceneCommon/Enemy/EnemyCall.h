/*
敵を読み込むためのクラス
作成者：杉山
作成日：2021/05/25
*/
#pragma once

//列挙型の使用
#include"EnemyType.h"


class EnemyCall
{
private:
	//座標情報
	enum class eEnemyCSV :int
	{
		POSITION_X,		//X座標
		POSITION_Y,		//Y座標
		POSITION_Z,		//Z座標
		PHASE_NUM,		//動き出すフェーズ数
		ENEMY_TYPE,		//敵の種類
	};

	//敵情報
	struct EnemyInfo
	{
		//敵の座標
		DirectX::SimpleMath::Vector3 mVectorESPosition;	//1,2,3番目の要素
		//フェーズ番号
		int mPhaseNumber;
		//敵の種類
		EnemyType mType;

		//コンストラクタ
		EnemyInfo()
			:mVectorESPosition()
			, mPhaseNumber()
			, mType(EnemyType::NONE)
		{}
	};
	//定数

	//実体化
	std::vector<EnemyInfo> mNormalEnemyInfo;	//通常敵数はステージによって可変
	EnemyInfo mBossEnemyInfo;					//ボス敵はステージに最大1体

public:
	//コンストラクタ
	EnemyCall();
	//デストラクタ
	~EnemyCall();
	//ファイル情報を返す
	EnemyInfo GetNormalEnemyStructer(const int& i)const {return mNormalEnemyInfo[i];}
	EnemyInfo GetBossEnemyStructer()const {return mBossEnemyInfo;}
	//要素数を返す
	int GetNormalEnemyStructerSize() const {return mNormalEnemyInfo.size();}
	//敵情報を指定する関数
	void LoadInfo(const std::string & filepath);
	//要素を初期化
	void Reset();

private:
	//CSVファイル名を指定
	void SetCSV(const std::string & filepath);
};