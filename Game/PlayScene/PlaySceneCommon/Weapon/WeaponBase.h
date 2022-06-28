/*
武器基底クラス
作成者：杉山
作成日：2021/09/14
*/
#pragma once

//列挙型の使用
#include "WeaponeType.h"
//所持
#include"../ObjectModel/ObjectModel.h"

class BulletManager;	//ポインタ保存用
class Player;			//ポインタ保存用

class WeaponBase
{
private:

	//武器モデル
	std::unique_ptr<ObjectModel> mpWeaponModel;

	//ポインタ保存用変数
	BulletManager* mpBulletManager;
	Player* mpPlayer;

	//総弾数
	int mMaxBulletNum;

	//攻撃力
	int mWeaponBulletAttackNum;

public:
	//コンストラクタ
	WeaponBase();

	//デストラクタ
	virtual ~WeaponBase() = default;

	//初期化
	virtual void Initialize() = 0;

	//描画
	virtual void Draw() = 0;

	//弾発射処理
	virtual void Shot() = 0;

	//リセット処理
	virtual void Reset() {}

	//モデルの取得
	ObjectModel* GetWeaponModel()const { return mpWeaponModel.get(); }

	//座標を設定する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position);

	//購入額を返す
	//基本的に派生先で上書き。
	virtual int GetWeaponPrice()const = 0;

	//ポインタを保存する
	void SetBulletManagerPointer(BulletManager* pBulletManager) { mpBulletManager = pBulletManager; }
	void SetPlayerPointer(Player* pPlayer) { mpPlayer = pPlayer; }

	//弾数のアクセサ
	int GetBulletNum() const { return mMaxBulletNum; }
	void SetBulletNum(const int& bulletnum) { mMaxBulletNum = bulletnum; }
	//弾を1発減らす
	void ReduceBulletNum() { mMaxBulletNum--; }

	//攻撃力のアクセサ
	void SetWeaponBulletAttackNum(const int& num) { mWeaponBulletAttackNum = num; }

	//武器を破棄する
	bool Destroy();


protected:
	//アクセサ
	BulletManager* GetBulletManager()const { return mpBulletManager; }
	Player* GetPlayer()const { return mpPlayer; }
	int GetWeaponBulletAttackNum()const { return mWeaponBulletAttackNum; }
};
