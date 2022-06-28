/*
敵ダメージState　～点滅～
作成者：杉山
作成日：2022/02/09
*/
#pragma once

//基底クラス
#include"EnemyDamageStateBase.h"
#include"../../../DamageTimer.h"

class EnemyDamageStateBlinking :public EnemyDamageStateBase
{
private:
	//敵点滅インターバル
	static const int ENEMY_BLINKING_INTERVAL;

	//計測タイマー
	std::unique_ptr<DamageTimer> mpDamageTimer;


public:

	//コンストラクタ
	EnemyDamageStateBlinking();
	//デストラクタ
	~EnemyDamageStateBlinking();
	//初期化処理
	 void Initialize(Enemy* pEnemy, EnemyMainStateDamage* pEnemyMainState)override;
	//リセット処理
	 void Reset()override;
	//更新処理
	 void Update()override;
	//描画処理
	void Draw()override;


};
