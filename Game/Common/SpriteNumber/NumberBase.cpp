/*
数字が浮く表現を行うクラスの基底クラス
作成者：杉山
作成日：2021/10/22
*/
#include"pch.h"
#include "NumberBase.h"


//透明度初期値
const float NumberBase::INIT_ALPHA = 1.f;	
//数字の数の最大数
const int NumberBase::MAX_NUMTYPE_NUM = 10;


/*==============================================
コンストラクタ
引数：なし
===============================================*/
NumberBase::NumberBase()
	:
	mTextureAlpha(INIT_ALPHA),
	mTextureKey()
{
}

/*==============================================
デストラクタ
===============================================*/
NumberBase::~NumberBase()
{
}

/*==============================================
取得した数字から必要な数字を選び出す:private
引数：作成する数字、桁数
返り値：必要な数字
===============================================*/
std::vector<int> NumberBase::ChooseNum(int num)
{
	//返り値用変数の宣言
	std::vector<int> returnNum;
	std::vector<int> instantNum;

	//1階回るごとに桁を一つ減らしていく
	for (int i = num; i >= 1; i /= MAX_NUMTYPE_NUM)
	{
		instantNum.push_back(i);
	}
	//０調節
	if (static_cast<int>(instantNum.size()) == 0)
	{
		instantNum.push_back(0);
	}

	//サイズを増やす
	returnNum.resize(instantNum.size());

	returnNum[0] = instantNum[instantNum.size() - 1];

	//実際に保存する値を算出する
	for (int i = static_cast<int>(returnNum.size()) - 1; i > 0; i--)
	{
		returnNum[i] = instantNum[i - 1] - (instantNum[i] * MAX_NUMTYPE_NUM);
	}

	//順番を元に戻す
	instantNum = returnNum;

	for (int i = 1; i < static_cast<int>(returnNum.size()); i++)
	{
		returnNum[i] = instantNum[static_cast<int>(returnNum.size()) - i];
	}

	return returnNum;
}

