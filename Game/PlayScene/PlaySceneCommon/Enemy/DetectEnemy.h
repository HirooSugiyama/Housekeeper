/*
敵衝突処理共通処理
作成者：杉山
作成日：2022/02/20
*/
#pragma once

//列挙型の使用
#include "Game/PlayScene/Effect/EffectType.h"

class Administrator;	//引数で使用

class DetectEnemy
{
private:

	//ポインタ保存用変数
	Administrator* mpAdministrator;

public:
	//アクセサ
	Administrator* GetAdministrator()const { return mpAdministrator; }
	void SetAdministrator(Administrator* pAdministrator) { mpAdministrator = pAdministrator; }
};
