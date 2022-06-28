/*
武器種を記した列挙型があるヘッダーファイル
作成者：杉山
作成日：2021/09/06
*/
#pragma once

//武器種
enum class eWeaponType
{
	NONE,				//装備なし
	MACHINE_GUN,		//機関銃
	BOMB,				//手りゅう弾
	ROCKET_LAUNCHER,	//ロケットランチャー
	PISTOL,				//ピストル
	BOOMERANG,			//ブーメラン
	NUM,				//種類数
};


