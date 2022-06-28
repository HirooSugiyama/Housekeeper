/*
��{�I�Ȓe�̈ړ�����
�쐬�ҁF���R
�쐬���F2021/10/16
*/

#include"pch.h"
#include "BulletStateNormalBullet.h"

//�O���錾
#include"Bullet.h"

//�֐��̎g�p
#include"../../PlaySceneCommon/ObjectModel/SphereModel.h"

/*==================
�R���X�g���N�^
�����F�Ȃ�
==================*/
BulletStateNormalBullet::BulletStateNormalBullet()
	:
	BulletStateBase()
{
}

/*=======================================
�ړ�����
�����F�Ȃ�
�Ԃ�l�F������͖��g�p(��State��Ŏg�p)
=======================================*/
bool BulletStateNormalBullet::Move()
{
	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//���W�֔��f
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	return false;
}


/*=================================
�e�Փˎ��̒ʏ�G�̏���
�����F�Ȃ�
�Ԃ�l�F�G�t�F�N�g�̎��
===================================*/
eEffectType BulletStateNormalBullet::HitNormalEnemy(Enemy* pEnemy)
{
	//���g�p�����̃G���[�悯����
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}
/*=================================
�e�Փˎ��̃{�X�G�̏���
�Ԃ�l�F�G�t�F�N�g�̎��
===================================*/
eEffectType BulletStateNormalBullet::HitBossEnemy(BossEnemy* pEnemy)
{
	//���g�p�����̃G���[�悯����
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}
/*=================================
�e�Փˎ��̔z���G�̏���
�����F�Ȃ�
�Ԃ�l�F�G�t�F�N�g�̎��
===================================*/
eEffectType BulletStateNormalBullet::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//���g�p�����̃G���[�悯����
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}