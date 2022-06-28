/*
弾管理クラス
作成者：杉山
作成日：2021/09/17
*/
#pragma once

//列挙型の使用
#include"../Weapon/WeaponeType.h"
#include"../../Effect/EffectType.h"

//所持
#include"Bullet.h"
#include"BulletType.h"


//前方宣言
class Bullet;			//所持
class BulletType;		//所持
class Enemy;			//当たり判定の引数で使用
class BossEnemy;		//当たり判定の引数で使用
class SubordinateEnemy;	//当たり判定の引数で使用
class BlockManager;		//当たり判定の引数で使用
class CameraBase;		//ポインタ保存用
class Player;			//ポインタ保存用
class EnemyManager;		//ポインタ保存用

class BulletStateBoomerang;	//所持

class BulletManager
{
private:

	//弾の最大数
	static const int BULLET_MAX_NUM = 50;

	//最大範囲
	static const float BULLET_MAX_POSITION_Z;

	//インターバル計測終了用初期化用定数
	static const int BULLET_INTERVAL_FINISH_NUM;

	//弾
	std::unique_ptr<Bullet> mpBullet[BULLET_MAX_NUM];

	//弾情報管理クラス
	std::unique_ptr<BulletType> mpBulletType;

	//弾発射インターバル判定フラグ
	bool mBulletShotIntervalFlag;

	//現在のインターバル用タイマー
	int mIntervalTimer;

	//現在の武器の弾の種類
	eWeaponType mWeaponType;

	//ポインタ保存用変数
	CameraBase* mpCamera;

	//ブーメランのみ唯一の物のため管理クラスで管理
	std::unique_ptr<BulletStateBoomerang> mpBoomerangBullet;

	//ポインタ保存用変数
	EnemyManager* mpEnemyManager;

public:

	//コンストラクタ
	BulletManager();
	//デストラクタ
	~BulletManager();
	//初期化処理
	void Initialize(CameraBase* pCamera, Player* pPlayer, EnemyManager* pEnemyManager);

	//弾生成処理
	bool Create(const DirectX::SimpleMath::Vector3& position);

	//更新処理
	void Update();
	//描画処理
	void Draw();

	//インターバル用タイマーをリセットする
	void ResetIntervalTimer() { mIntervalTimer = 0; }

	//武器種のアクセサ
	void SetWeaponType(const eWeaponType& type) { mWeaponType = type; }

	//弾と敵の衝突判定を取る
	int ChackHitBulletEnemy(Enemy* pEnemy);

	//弾とボス敵の衝突判定を取る
	int ChackHitBulletBossEnemy(BossEnemy* pEnemy);

	//弾と配下敵の衝突判定を取る
	int ChackHitBulletSubordinateEnemy(SubordinateEnemy* pEnemy);

	//プレイヤーと弾の衝突判定
	void ChackHitBulletPlayer(Player* pPlayer);

	//ブロックとの衝突判定を回す関数
	void RoolChackHitBlock(BlockManager* pBlockManager);

	//ブーメランのポインタを渡す
	BulletStateBoomerang* GetBoomerangBullet() const { return mpBoomerangBullet.get(); }

	//弾の管理情報のアクセサ
	BulletType* GetBulletType() const { return mpBulletType.get(); }

private:

	//範囲外処理
	void OutOfRange();

	//インターバル計測
	bool MeasureInterval();

};
