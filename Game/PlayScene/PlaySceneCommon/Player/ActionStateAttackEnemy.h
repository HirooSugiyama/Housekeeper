/*
プレイヤーの行動状態分けステートパターン
作成者：杉山
作成日：2021/09/14
*/
#pragma once

//基底クラス
#include"ActionStateBase.h"

//列挙型の使用
#include"../Weapon/WeaponeType.h"

//所持
#include"../Weapon/WeaponHand.h"

//前方宣言
class WeaponBase;	//武器基底クラス

class WeaponManager;//武器管理クラス(ポインタ保存用)
class BulletManager;//弾管理クラス(ポインタ保存用)

class ActionStateAttackEnemy :public ActionStateBase
{
private:
	//所持できる武器
	enum class ePositionsessionWeapon
	{
		HAND,
		STRONG_WEAPON,
	};


	//プレイヤーの座標と武器モデルの座標の差
	static const DirectX::SimpleMath::Vector3 WEPON_MODEL_PLAYER_SHIFT_POSITION;


	//武器管理クラス
	std::unique_ptr<WeaponHand> mpHand;	//こっちは固定
	WeaponBase* mpStrongWeapon;			//こっちは可変

	//ポインタ保存用
	Player* mpPlayer;
	WeaponManager* mpWeaponManager;
	BulletManager* mpBulletManager;

	//現在装備している武器
	eWeaponType mUseWeapon;

	//攻撃判定フラグ(true→攻撃できる)
	bool mAttackFlag;

	//マシンガン専用SEID保存用変数
	int mMachinGunSEID;

public:

	//コンストラクタ
	ActionStateAttackEnemy();
	//デストラクタ
	~ActionStateAttackEnemy();
	//初期化処理
	void Initialize(Player* pPlayer);
	//更新処理
	void Update();
	//State開始時の初期化処理
	void Reset();
	//描画処理
	void Draw();

	//強い武器を持ち変える
	void ChangeStrongWeapon(const eWeaponType& weapon);

	//弱攻撃を返す処理
	WeaponHand* GetHand()const { return mpHand.get(); }
	//強攻撃を返す処理
	WeaponBase* GetStrongWeapon()const { return mpStrongWeapon; }

	//ポインタ保存用変数のアクセサ
	void SetWeaponManagerPointer(WeaponManager* pWeaponManager) { mpWeaponManager = pWeaponManager; }
	void SetBulletManagerPointer(BulletManager* pBulletManager) { mpBulletManager = pBulletManager; }


private:
	//強い攻撃の攻撃処理
	void StrongWeaponAttack();

	//ブーメラン専用処理
	void BoomerangUpdate();
};
