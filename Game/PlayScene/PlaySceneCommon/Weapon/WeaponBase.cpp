/*
武器基底クラス
作成者：杉山
作成日：2021/10/14
*/


#include"pch.h"
#include "WeaponBase.h"

//前方宣言
#include"../Bullet/BulletManager.h"
#include"../Player/Player.h"


/*=========================
コンストラクタ
引数：なし
=========================*/
WeaponBase::WeaponBase()
	:
	mpWeaponModel(nullptr),
	mpBulletManager(nullptr),
	mpPlayer(nullptr),
	mMaxBulletNum(0),
	mWeaponBulletAttackNum(0)
{
	mpWeaponModel = std::make_unique<ObjectModel>();
}

/*=======================
座標の設定
引数：座標
返り値：なし
=========================*/
void WeaponBase::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	mpWeaponModel->SetPosition(position);
}

/*====================================
武器を破棄する
引数：なし
返り値：武器を破棄するか否か
======================================*/
bool WeaponBase::Destroy()
{
	if (mMaxBulletNum <= 0)
	{
		return true;
	}
	return false;
}
