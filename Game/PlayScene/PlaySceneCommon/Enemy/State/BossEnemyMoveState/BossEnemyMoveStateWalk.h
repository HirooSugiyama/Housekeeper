/*
ボス敵移動State　〜歩行〜
作成者：杉山
作成日：2022/02/12
*/
#pragma once

//基底クラス
#include"BossEnemyMoveStateBase.h"

class BossEnemyMoveStateWalk :public BossEnemyMoveStateBase
{
private:
	//移動速度
	static const float ENEMY_WALK_SPEED;

public:

	//コンストラクタ
	BossEnemyMoveStateWalk();
	//デストラクタ
	~BossEnemyMoveStateWalk();
	//初期化処理
	void Initialize(IEnemy* pBossEnemy, BossEnemyMainStateMove* pMoveState)override;

	//向き設定処理
	void SetAngle()override;

	//移動速度設定
	DirectX::SimpleMath::Vector3 GetMoveVelocity()override;
};
