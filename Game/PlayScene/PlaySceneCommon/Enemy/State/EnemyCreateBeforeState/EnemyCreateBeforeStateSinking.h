/*
敵生成前State	～沈没～
作成者：杉山
作成日：2022/02/07
*/
#pragma once

//基底クラス
#include"EnemyCreateBeforeStateBase.h"

class EnemyCreateBeforeStateSinking : public EnemyCreateBeforeStateBase
{
private:

	//影を拡大描画
	static const DirectX::SimpleMath::Vector2 ENEMY_SHADOW_SCLAE_UP;
	//影の高さを調節
	static const float ENEMY_SHADOW_SHIFT_POSITIONY;


public:

	//コンストラクタ
	EnemyCreateBeforeStateSinking();
	//デストラクタ
	~EnemyCreateBeforeStateSinking()override;
	//初期化処理
	void Initialize(EnemyMainStateCreateBefore* pEnemyMainState, IEnemy* pEnemy)override;
	//更新処理
	void Update()override {};
	//描画処理
	void Draw()override;

};
