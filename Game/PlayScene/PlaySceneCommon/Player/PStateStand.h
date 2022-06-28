/*
プレイヤーの状態分けステートパターン：立ち状態
作成者：杉山
作成日：2021/06/15
*/
#pragma once
#include"PlayerStateBase.h"


class ObjectSpriteModel;

class PStateStand :public PlayerStateBase
{
private:
	//変数
	//Playerオブジェクトへ保存用のポインタ
	Player* mpPlayer;

public:
	//関数
	//コンストラクタ
	PStateStand();
	//デストラクタ
	~PStateStand();
	//初期化処理
	void Initialize(Player* pPlayer)override;
	//State開始時の初期化処理
	void Reset()override {}
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

};