/*
敵基本State　～消滅～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyMainStateBase.h"

class EnemyMainStateDisappearance : public EnemyMainStateBase
{
private:


public:

	//コンストラクタ
	EnemyMainStateDisappearance();
	//デストラクタ
	~EnemyMainStateDisappearance();
	//初期化処理
	void Initialize(IEnemy* pEnemy)override;
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

};
