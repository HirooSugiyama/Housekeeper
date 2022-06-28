/*
所持金管理ファイル
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"
#include"Money.h"


//クラス外部で初期化
std::unique_ptr<Money> Money::sMoney = nullptr;

/*===================================
コンストラクタ
引数：なし
===================================*/
Money::Money()
	:
	mFilepath("none"),
	mPossessionMoney()
{
}

/*=================================
自身のインスタンス
引数：なし
返り値：自身のインスタンス
===================================*/
Money& Money::GetMoneyInstance()
{
	if (sMoney == nullptr)
	{
		sMoney.reset(new Money());
	}
	return *sMoney;
}

/*=================================
ファイル名の設定
引数：ファイルパス
返り値：なし
===================================*/
void Money::LoadFileSet(std::string filepath)
{
	//引数の保存
	mFilepath = filepath;

	//金額の初期設定
	this->MoneyInit();
}

/*===================================
所持金の初期設定:private
引数：なし
返り値：なし
===================================*/
void Money::MoneyInit()
{
	//例外処理
	Utility::FileError(mFilepath);

	//ファイル変換
	std::ifstream ifs(mFilepath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//引き出す
	std::getline(ifs, lineBuf);


	mPossessionMoney = static_cast<int>(atof(lineBuf.c_str()));
}

