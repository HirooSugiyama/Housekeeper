/*
武器管理クラス
作成者：杉山
作成日：2021/09/14
*/
#include"pch.h"
#include "WeaponManager.h"

//前方宣言
#include"WeaponBase.h"


/*===============================
コンストラクタ
引数：なし
===============================*/
WeaponManager::WeaponManager()
	:
	mpWeaponmachineGun(nullptr),
	mpWeaponBomb(nullptr),
	mpWeaponBoomerang(nullptr),
	mpWeaponPistol(nullptr),
	mpWeaponRocketLauncher(nullptr)
{
	mpWeaponmachineGun = std::make_unique<WeaponMachineGun>();
	mpWeaponBomb = std::make_unique<WeaponBomb>();
	mpWeaponBoomerang = std::make_unique<WeaponBoomerang>();
	mpWeaponPistol = std::make_unique<WeaponPistol>();
	mpWeaponRocketLauncher = std::make_unique<WeaponRocketLauncher>();
}


/*===============================
デストラクタ
===============================*/
WeaponManager::~WeaponManager()
{
}


/*===============================
初期化処理
引数：弾管理クラスのポインタ
返り値：なし
===============================*/
void WeaponManager::Initialize(BulletManager* pBulletManager)
{
	//初期化処理
	mpWeaponmachineGun->Initialize();
	mpWeaponBomb->Initialize();
	mpWeaponBoomerang->Initialize();
	mpWeaponPistol->Initialize();
	mpWeaponRocketLauncher->Initialize();

	//ポインタ保存処理
	mpWeaponmachineGun->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponBomb->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponBoomerang->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponPistol->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponRocketLauncher->
		SetBulletManagerPointer(pBulletManager);

}


/*=========================================
武器を変更する処理
引数	：武器の種類(列挙)
返り値	：引数に応じた武器のポインタ
=========================================*/
WeaponBase* WeaponManager::GetWeapon(const eWeaponType& type)
{
	//引数に応じて返すものを変える
	switch (type)
	{
		case eWeaponType::MACHINE_GUN:
		{
			return (WeaponBase*)mpWeaponmachineGun.get();
			break;
		}
		case eWeaponType::BOMB:
		{
			return (WeaponBase*)mpWeaponBomb.get();
			break;
		}
		case eWeaponType::ROCKET_LAUNCHER:
		{
			
			return (WeaponBase*)mpWeaponRocketLauncher.get();
			break;
		}
		case eWeaponType::PISTOL:
		{
			return (WeaponBase*)mpWeaponPistol.get();
			break;
		}
		case eWeaponType::BOOMERANG:
		{
			return (WeaponBase*)mpWeaponBoomerang.get();
			break;
		}
	}
	return nullptr;
}
