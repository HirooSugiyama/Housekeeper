/*
武器管理クラス
作成者：杉山
作成日：2021/09/14
*/
#pragma once

//列挙型の使用
#include"WeaponeType.h"

#include"WeaponMachineGun.h"
#include"WeaponBomb.h"
#include"WeaponBoomerang.h"
#include"WeaponPistol.h"
#include"WeaponRocketLauncher.h"


//前方宣言
class WeaponBase;			//返り値で使用
class BulletManager;		//ポインタ保存関数の引数で使用

class WeaponManager
{
private:

	//各種武器
	std::unique_ptr<WeaponMachineGun> mpWeaponmachineGun;
	std::unique_ptr<WeaponBomb> mpWeaponBomb;
	std::unique_ptr<WeaponBoomerang> mpWeaponBoomerang;
	std::unique_ptr<WeaponPistol> mpWeaponPistol;
	std::unique_ptr<WeaponRocketLauncher> mpWeaponRocketLauncher;

public:
	//コンストラクタ
	WeaponManager();
	//デストラクタ
	~WeaponManager();
	//初期化
	void Initialize(BulletManager* pBulletManager);

	//武器を変更する処理
	WeaponBase* GetWeapon(const eWeaponType& type);


};