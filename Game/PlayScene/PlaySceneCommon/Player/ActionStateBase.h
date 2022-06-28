/*
プレイヤーの行動状態分けステートパターン
作成者：杉山
作成日：2021/09/14
*/
#pragma once

#include"Player.h"//ポインタの都合上


class ActionStateBase
{

protected:
	//コンストラクタ
	ActionStateBase() = default;
	//デストラクタ
	virtual ~ActionStateBase() = default;

public:
	//初期化処理
	virtual void Initialize(Player* pPlayer) = 0;
	//更新処理
	virtual void Update() = 0;
	//State開始時の初期化処理
	virtual void Reset() = 0;
	//描画処理
	virtual void Draw() = 0;

};
