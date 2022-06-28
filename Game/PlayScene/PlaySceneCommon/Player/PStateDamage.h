/*
プレイヤーの状態分けステートパターン：やられ状態
作成者：杉山
作成日：2021/06/15
*/
#pragma once
#include"PlayerStateBase.h"

class DamageTimer;

class PStateDamage :public PlayerStateBase
{
private:
	//定数
	//プレイヤー点滅インターバル
	static const int PLAYER_BLINKING_INTERVAL;
	
	//変数
	//Playerオブジェクトへ保存用のポインタ
	Player* mpPlayer;

	std::unique_ptr<DamageTimer> mpDamageTimer;

public:
	//関数
	//コンストラクタ
	PStateDamage();
	//デストラクタ
	~PStateDamage();

	//初期化処理
	void Initialize(Player* pPlayer)override;
	//State開始時の初期化処理
	void Reset()override {}
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;
};