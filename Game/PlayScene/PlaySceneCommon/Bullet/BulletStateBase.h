/*
弾の移動処理の基底クラス
作成者：杉山
作成日：2021/10/16
*/
#pragma once

//列挙型の使用
#include"Game/PlayScene/Effect/EffectType.h"

//持ち主
class Bullet;

//引数で使用
class Enemy;
class BossEnemy;
class SubordinateEnemy;

class BulletStateBase
{
private:
	//持ち主
	Bullet* mpBullet;

protected:
	//コンストラクタ
	BulletStateBase()
		:mpBullet(nullptr)
	{}

	//デストラクタ
	virtual ~BulletStateBase() = default;

public:
	//アクセサ
	void SetBuletPointer(Bullet* pBullet) { mpBullet = pBullet; }
	Bullet* GetBullet() { return mpBullet; }

	//移動処理
	virtual bool Move() = 0;

	//描画処理
	virtual void Draw(){}

	//敵衝突時の処理
	virtual eEffectType HitNormalEnemy(Enemy* pEnemy) = 0;
	virtual eEffectType HitBossEnemy(BossEnemy* pEnemy) = 0;
	virtual eEffectType HitSubordinateEnemy(SubordinateEnemy* pEnemy) = 0;
};
