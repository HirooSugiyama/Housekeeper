/*
Effect簡易構造体で使用する情報を保存するヘッダーファイル
作成者：杉山
作成日：2021/09/19
*/
#pragma once

//エフェクトの種類
enum class eEffectType
{
	NONE,
	BOMB,		//爆発
	SLASH,		//突き
	SPAWN,		//出現
	CLAW,		//爪攻撃
	DISAPPEAR,	//消滅
	DESTROY,	//破壊

	NUM,	//エフェクトの種類数
};

