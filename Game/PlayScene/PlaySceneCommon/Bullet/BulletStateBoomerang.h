/*
ブーメランの移動処理
作成者：杉山
作成日：2021/10/16
*/

#pragma once

//列挙型の使用
#include"../Weapon/BoomerangState.h"

//基底クラス
#include"BulletStateBase.h"
//所持
#include"../Administrator/Timer.h"

//前方宣言
class Player;	//ポインタ取得

class BulletStateBoomerang :public BulletStateBase
{
private:

	//飛んでいく距離
	static const float BOOMERANG_FLY_DISTANCE;

	//停滞時間
	static const int BOOMERANG_STAGNATION;

	//座標最小値
	static const float BULLET_MIN_POSITION_Z;

	//回転速度
	static const float BULLET_ROT_VELOCITY;

	//速度減退割合
	static const float BULLET_VELOCITY_DECLINE;

	//最低速度
	static const float BULLET_MIN_VELOCITY;

	//ブーメランの飛距離追加値
	static const float BULLET_FLY_DIS_UP_NUM;

	//実態化
	eBoomerangState mState;

	//飛んでいく距離
	float mFlyDistance;

	//弾の飛ぶ方向
	DirectX::SimpleMath::Vector3 mBoomerangAngle;

	//弾の速度
	float mBoomerangVelocity;

	//ポインタ保存用変数
	Player* mpPlayer;
	std::unique_ptr<Timer> mpTimer;

	//場外フラグ
	bool mOutOfRangeFlag;

	float mFlyDistanceNum;

public:

	//コンストラクタ
	BulletStateBoomerang();

	//デストラクタ
	~BulletStateBoomerang()override = default;

	//移動処理
	bool Move()override;

	//ブーメランの状態のアクセサ
	void ChangeBoomerangState(const eBoomerangState& state) { mState = state; }
	eBoomerangState GetBoomerangState()const { return mState; }

	//プレイヤーの座標のポインタを保存する
	void SavePlayerPointer(Player* pPlayer) {mpPlayer = pPlayer;}

	//リセット処理
	void Reset();

	//場外フラグのアクセサ
	bool GetOutOfRangeFlag() const { return mOutOfRangeFlag; }

	//飛距離追加
	void DistanceAddValue();

	//敵衝突時の処理
	eEffectType HitNormalEnemy(Enemy* pEnemy)override;
	eEffectType HitBossEnemy(BossEnemy* pEnemy)override;
	eEffectType HitSubordinateEnemy(SubordinateEnemy* pEnemy)override;

private:
	//弾の回転処理
	void RotBullet();

	//速度減退処理
	void SlowDown();

};