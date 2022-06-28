/*
��{�I�Ȓe�̈ړ�����
�쐬�ҁF���R
�쐬���F2021/10/16
*/

#pragma once


//���N���X
#include"BulletStateBase.h"


class BulletStateNormalBullet :public BulletStateBase
{
public:

	//�R���X�g���N�^
	BulletStateNormalBullet();

	//�f�X�g���N�^
	~BulletStateNormalBullet()override = default;

	//�ړ�����
	bool Move()override;

	//�G�Փˎ��̏���
	eEffectType HitNormalEnemy(Enemy* pEnemy)override;
	eEffectType HitBossEnemy(BossEnemy* pEnemy)override;
	eEffectType HitSubordinateEnemy(SubordinateEnemy* pEnemy)override;
};