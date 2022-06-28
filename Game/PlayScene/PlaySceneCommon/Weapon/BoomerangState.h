/*
ブーメランの現在の状態を表す
作成者：杉山
作成日：2021/10/16
*/

#pragma once

//ブーメランの現在の状態
enum class eBoomerangState
{
	NONE,
	SHOT,
	CALCULATION,
	RETURN,
	CATCH,
};

