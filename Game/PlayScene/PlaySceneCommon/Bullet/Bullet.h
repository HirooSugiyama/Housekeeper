/*
弾クラス
作成者：杉山
作成日：2021/09/17
*/
#pragma once

//列挙型の使用
#include"../Weapon/WeaponeType.h"

//所持
#include"../ObjectModel/SphereModel.h"
#include"BulletStateNormalBullet.h"
#include"BulletStateExplosion.h"

//前方宣言
struct BulletInfomation;		//引数で使用
struct Sphere;					//返り値で使用

class Enemy;					//引数で使用
class BossEnemy;				//引数で使用
class SubordinateEnemy;			//引数で使用


class BulletStateBase;			//状態分け基底クラス
class BulletStateNormalBullet;	//状態分け基底クラス
class BulletStateBoomerang;		//状態分け基底クラス
class BulletStateExplosion;		//状態分け基底クラス
	
class Bullet
{
private:

	//当たり判定の半径
	static const float COLLIDER_RADIUS;

	//当たり判定拡大係数
	static const float COLLIDER_RADIUS_EXPANSION;

	//ユニークポインタ
	std::unique_ptr<SphereModel> mpBulletModel;

	//弾の攻撃力
	int mBulletAttackNum;

	//弾の速度
	float mBulletVelocity;

	//現在の弾の持ち主
	eWeaponType mWeaponType;

	//状態分け
	BulletStateBase* mpStateBase;
	std::unique_ptr<BulletStateNormalBullet> mpNormalBullet;
	std::unique_ptr<BulletStateExplosion> mpExplosion;
	BulletStateBoomerang* mpBoomerangBullet;			//唯一の物のため管理クラスから取得する

	//弾爆発フラグ
	bool mExplosionFlag;

public:

	//コンストラクタ
	Bullet();
	//デストラクタ
	~Bullet();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	//作成処理
	void Create(const DirectX::SimpleMath::Vector3& position, const eWeaponType& type);

	//未使用状態への変更関数
	void SelfDestroy();


	//使用中かどうかを返すアクセサ
	bool GetUseFlag()const;

	//Z座標を返す
	float GetBulletPositionZ()const;

	//弾情報保存用関数
	void SetBulletInfomation(const  BulletInfomation& pBulletInfomation);

	//攻撃力のアクセサ
	int GetBulletAttackNum()const { return mBulletAttackNum; }

	//当たり判定のアクセサ
	Sphere* GetBulletModelCollider()const;

	//弾の種類のアクセサ
	eWeaponType GetBulletWeaponType() const { return mWeaponType; }

	//モデルの座標のアクセサ
	SphereModel* GetBulletModel()const { return mpBulletModel.get(); }

	//弾の速度のアクセサ
	float GetBulletVelocity()const { return mBulletVelocity; }

	//ポインタを受け取る
	void SetBoomerangPointer(BulletStateBoomerang* pBoomerang) { mpBoomerangBullet = pBoomerang; }

	//弾爆発フラグのアクセサ
	void SetExplosionFlag(const bool& flag) { mExplosionFlag = flag; }
	bool GetExplosionFlag() const { return mExplosionFlag; }

	//当たり判定を倍にする
	void SetDoubleCollider();


	//弾衝突時の敵の処理
	bool HitNormalEnemy(Enemy* pEnemy);
	bool HitBossEnemy(BossEnemy* pEnemy);
	bool HitSubordinateEnemy(SubordinateEnemy* pEnemy);

private:
	//状態変更関数
	void ChangeStateNormalBullet() { mpStateBase = (BulletStateBase*)mpNormalBullet.get(); }
	void ChangeStateBoomerang() { mpStateBase = (BulletStateBase*)mpBoomerangBullet; }
	void ChangeStateExplosion() { mpStateBase = (BulletStateBase*)mpExplosion.get(); }

	//当たり判定生成処理
	void SetCollider();

	//エフェクト作成
	void SetEffect(const eEffectType& type, const DirectX::SimpleMath::Vector3& position);
};

