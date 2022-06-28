/*
所持金管理ファイル
作成者：杉山
作成日：2021/10/21
*/
#pragma once



class Money final
{
private:

	////自身
	static std::unique_ptr<Money> sMoney;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	Money(const Money& money) = delete;
	Money operator=(const  Money& money) = delete;

	//ファイル名
	std::string mFilepath;
	//所持金額
	int mPossessionMoney;

	//コンストラクタ
	Money();

public:

	//自身のインスタンス
	static Money& GetMoneyInstance();

	//ファイル名の設定
	void LoadFileSet(std::string filepath);

	//金額を引数分引く
	void ReduceMoney(const int& moneynum) { mPossessionMoney -= moneynum; }
	//金額の上書き
	void SetMoney(const int& moneynum) { mPossessionMoney = moneynum; }

	//金額を取得
	int GetMoney()const { return mPossessionMoney; }
private:

	//金額の初期化
	void MoneyInit();

};
