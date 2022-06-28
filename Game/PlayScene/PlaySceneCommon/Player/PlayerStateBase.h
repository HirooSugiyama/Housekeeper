/*
プレイヤーの状態分けステートパターン
作成者：杉山
作成日：2021/06/15
*/
#pragma once

#include"Player.h"//ポインタの都合上

enum class eStatePlayer
{
	STAND,			
	WALK,			
	DAMAGE,
};

class PlayerStateBase
{

protected:
	//コンストラクタ
	PlayerStateBase()=default;
	//デストラクタ
	virtual ~PlayerStateBase() = default;

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
