/*
������N���X
�쐬�ҁF���R
�쐬���F2021/10/14
*/


#include"pch.h"
#include "WeaponBase.h"

//�O���錾
#include"../Bullet/BulletManager.h"
#include"../Player/Player.h"


/*=========================
�R���X�g���N�^
�����F�Ȃ�
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
���W�̐ݒ�
�����F���W
�Ԃ�l�F�Ȃ�
=========================*/
void WeaponBase::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	mpWeaponModel->SetPosition(position);
}

/*====================================
�����j������
�����F�Ȃ�
�Ԃ�l�F�����j�����邩�ۂ�
======================================*/
bool WeaponBase::Destroy()
{
	if (mMaxBulletNum <= 0)
	{
		return true;
	}
	return false;
}
