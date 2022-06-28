/*
爆発する弾の移動処理
作成者：杉山
作成日：2021/10/16
*/

#pragma once


//基底クラス
#include"BulletStateBase.h"


class BulletStateExplosion :public BulletStateBase
{
private:
	//重力定数
	static const float GRAVITY;

	//初期速度
	static const float FIRST_VELOCITY;

	//最初の高さ
	static const float FIRST_HEIGHT;

	//エフェクトを出現させる座標
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;



	//速度
	float mBulletVelocity;
	//高さ
	float mBulletHeight;

public:
	//コンストラクタ
	BulletStateExplosion();

	//デストラクタ
	~BulletStateExplosion()override = default;

	//移動処理
	bool Move()override;

	//描画処理
	void Draw()override;

	//敵衝突時の処理
	eEffectType HitNormalEnemy(Enemy* pEnemy)override;
	eEffectType HitBossEnemy(BossEnemy* pEnemy)override;
	eEffectType HitSubordinateEnemy(SubordinateEnemy* pEnemy)override;

private:
	//リセット処理
	void Reset();
};