/*
�e�̈ړ������̊��N���X
�쐬�ҁF���R
�쐬���F2021/10/16
*/
#pragma once

//�񋓌^�̎g�p
#include"Game/PlayScene/Effect/EffectType.h"

//������
class Bullet;

//�����Ŏg�p
class Enemy;
class BossEnemy;
class SubordinateEnemy;

class BulletStateBase
{
private:
	//������
	Bullet* mpBullet;

protected:
	//�R���X�g���N�^
	BulletStateBase()
		:mpBullet(nullptr)
	{}

	//�f�X�g���N�^
	virtual ~BulletStateBase() = default;

public:
	//�A�N�Z�T
	void SetBuletPointer(Bullet* pBullet) { mpBullet = pBullet; }
	Bullet* GetBullet() { return mpBullet; }

	//�ړ�����
	virtual bool Move() = 0;

	//�`�揈��
	virtual void Draw(){}

	//�G�Փˎ��̏���
	virtual eEffectType HitNormalEnemy(Enemy* pEnemy) = 0;
	virtual eEffectType HitBossEnemy(BossEnemy* pEnemy) = 0;
	virtual eEffectType HitSubordinateEnemy(SubordinateEnemy* pEnemy) = 0;
};
