/*
指定された物体の影を表示するクラス
作成者：杉山
作成日：2021/09/23
*/
#include "pch.h"
#include "Shadow.h"

/*=================
コンストラクタ
引数：なし
====================*/
Shadow::Shadow()
	:
	FlatPolygon()
{
}

/*=========================
デストラクタ
=========================*/
Shadow::~Shadow()
{

}

/*================
ラップした初期化
引数：なし
返り値：なし
==================*/
void Shadow::WrapInitialize()
{
	//派生元の初期化処理
	this->Initialize();

	//画像を設定する
	this->SetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SHADOW));
}

