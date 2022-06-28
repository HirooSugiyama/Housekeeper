/*
�e�N���X
�쐬�ҁF���R
�쐬���F2021/09/17
*/
#include"pch.h"
#include"Bullet.h"

//�O���錾
#include"BulletType.h"
#include"BulletStateBase.h"

#include"../Enemy/Enemy.h"
#include"../Enemy/BossEnemy.h"
#include"../Enemy/SubordinateEnemy.h"

//�Ăяo��
#include "Game/PlayScene/Effect/EffectManager.h"


//�����蔻��̔��a
const float Bullet::COLLIDER_RADIUS = 1.f;
//�����蔻��g��W��
const float Bullet::COLLIDER_RADIUS_EXPANSION = 2.5f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Bullet::Bullet()
	:
	mpBulletModel(),
	mBulletAttackNum(),
	mBulletVelocity(),
	mWeaponType(eWeaponType::NONE),
	mpStateBase(nullptr),
	mpNormalBullet(nullptr),
	mpExplosion(nullptr),
	mpBoomerangBullet(nullptr),
	mExplosionFlag(false)
{
	mpBulletModel = std::make_unique<SphereModel>();

	//��ԕ���
	mpNormalBullet = std::make_unique<BulletStateNormalBullet>();
	mpExplosion = std::make_unique<BulletStateExplosion>();
}

/*===================================
�f�X�g���N�^
===================================*/
Bullet::~Bullet()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::Initialize()
{
	//���g�p��Ԃŏ�����
	mpBulletModel->SetModelUseFlag(false);

	//��ԕ�����Ƀ|�C���^��ۑ�
	mpNormalBullet->SetBuletPointer(this);
	mpExplosion->SetBuletPointer(this);
}

/*=================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::Update()
{
	//��Ԗ��̈ړ��������s��
	bool deleteflag = mpStateBase->Move();

	//�����͈͊O�ɏo����
	if (deleteflag)
	{
		//�u�[���������폜����
		//�A�N�Z�X�������������Ȃ̂�delete�͂��Ȃ��B
		mpBoomerangBullet = nullptr;
		this->SelfDestroy();
	}

	//�����蔻�蔽�f����
	this->SetCollider();

}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::Draw()
{
	mpBulletModel->Draw();
}

/*=================================
�e�쐬����
�����F�o�����W�A�e�̎��
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::Create(const DirectX::SimpleMath::Vector3& position, const eWeaponType& type)
{
	//�g�p��Ԃɂ���
	mpBulletModel->SetModelUseFlag(true);

	//���W�̐ݒ�
	mpBulletModel->SetPosition(position);

	//�e�̎�ނ̕ۑ�
	mWeaponType = type;

	//�e�̎�ނɂ���ď�����ς���
	switch (mWeaponType)
	{
		case eWeaponType::MACHINE_GUN:
		case eWeaponType::PISTOL:			//NoBreak
		case eWeaponType::ROCKET_LAUNCHER://NoBreak
		{
			//�ʏ�e�̐ݒ�
			this->ChangeStateNormalBullet();

			break;
		}
		case eWeaponType::BOMB:
		{
			//�����e�̐ݒ�
			this->ChangeStateExplosion();
			break;
		}
		case eWeaponType::BOOMERANG:
		{
			this->ChangeStateBoomerang();

			break;
		}

	}
}

/*=================================
���g�p��Ԃւ̕ύX�֐�
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::SelfDestroy()
{
	if (mpBulletModel->GetModelUseFlag())
	{
		//�����蔻��������l��
		mpBulletModel->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);

		//���g�p��Ԃɂ���
		mpBulletModel->SetModelUseFlag(false);

		//�����t���O������
		mExplosionFlag = false;
	}
}

/*=================================
�g�p�����ǂ�����Ԃ��A�N�Z�T
�����F�Ȃ�
�Ԃ�l�F�g�p�t���O
===================================*/
bool Bullet::GetUseFlag()const
{
	return mpBulletModel->GetModelUseFlag();
}

/*===================================
Z���W��Ԃ�
�Ԃ�l�F���f����Z���W
===================================*/
float Bullet::GetBulletPositionZ()const
{
	return mpBulletModel->GetPosition().z;
}

/*===================================
�e���ۑ��p�֐�
�����F�e���
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::SetBulletInfomation(const BulletInfomation& pBulletInfomation)
{
	//���f���̎擾
	mpBulletModel->SetModel(pBulletInfomation.mBulletModel);

	//�U���͂̐ݒ�
	mBulletAttackNum = pBulletInfomation.mBulletAttackNum;

	//�g�嗦�̐ݒ�
	mpBulletModel->SetScale(pBulletInfomation.mBulletScale);

	//�e�̑��x�̐ݒ�
	mBulletVelocity = pBulletInfomation.mBulletVelocityZ;
}

/*===================================
�ړ�����
�����F�Ȃ�
�Ԃ�l�F�����蔻��
===================================*/
Sphere* Bullet::GetBulletModelCollider()const
{
	return mpBulletModel->GetSphereCollider();
}

/*==================================
�����蔻�萶������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::SetCollider()
{
	//�ȗ����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 position = mpBulletModel->GetPosition();
	float scale = COLLIDER_RADIUS;

	//�����蔻���ݒ肷��
	mpBulletModel->SetSphereCollider(position,scale);
}

/*=================================
�����蔻���{�ɂ���
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::SetDoubleCollider()
{
	//�ȗ����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 position = mpBulletModel->GetPosition();
	float scale = COLLIDER_RADIUS* COLLIDER_RADIUS_EXPANSION;

	//�����蔻���ݒ肷��
	mpBulletModel->SetSphereCollider(position, scale);
}


/*=================================
�e�Փˎ��̒ʏ�G�̏���
�����F�ʏ�G�̃|�C���^
�Ԃ�l�F�G���j�t���O
===================================*/
bool Bullet::HitNormalEnemy(Enemy* pEnemy)
{
	//���j�t���O
	bool breakflag = false;

	//�G�t�F�N�g�ύX�p�ϐ�
	eEffectType type = eEffectType::NONE;

	//�G�Ƀ_���[�W��^����
	breakflag = pEnemy->Damage(mBulletAttackNum, pEnemy->GetEnemyHP());


	//�e��ɉ���������
	type = mpStateBase->HitNormalEnemy(pEnemy);


	//�G�t�F�N�g��ݒ肷��
	this->SetEffect(type, pEnemy->GetEnemyModel()->GetPosition());

	return breakflag;
}

/*=================================
�e�Փˎ��̃{�X�G�̏���
�����F�{�X�G�̃|�C���^
�Ԃ�l�F�G���j�t���O
===================================*/
bool Bullet::HitBossEnemy(BossEnemy* pEnemy)
{
	//���j�t���O
	bool breakflag = false;

	//�G�t�F�N�g�ύX�p�ϐ�
	eEffectType type = eEffectType::NONE;

	//�G�Ƀ_���[�W��^����
	breakflag = pEnemy->Damage(mBulletAttackNum, pEnemy->GetEnemyHP());

	//�e��ɉ���������
	type = mpStateBase->HitBossEnemy(pEnemy);

	//�G�t�F�N�g��ݒ肷��
	this->SetEffect(type, pEnemy->GetEnemyModel()->GetPosition());

	return breakflag;
}

/*=================================
�e�Փˎ��̔z���G�̏���
�����F�z���G�̃|�C���^
�Ԃ�l�F�G���j�t���O
===================================*/
bool Bullet::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//���j�t���O
	bool breakflag = false;

	//�G�t�F�N�g�ύX�p�ϐ�
	eEffectType type = eEffectType::NONE;

	//�G�Ƀ_���[�W��^����
	breakflag = pEnemy->Damage(mBulletAttackNum, pEnemy->GetEnemyHP());

	//�e��ɉ���������
	type = mpStateBase->HitSubordinateEnemy(pEnemy);

	//�G�t�F�N�g��ݒ肷��
	this->SetEffect(type, pEnemy->GetEnemyModel()->GetPosition());

	return breakflag;
}



/*=================================
�G�t�F�N�g��ݒ肷��:private
�����F�G�t�F�N�g�̎�ށA���W
�Ԃ�l�F�Ȃ�
===================================*/
void Bullet::SetEffect(const eEffectType& type, const DirectX::SimpleMath::Vector3& position)
{
	//�G�t�F�N�g�}�l�[�W���[�̎擾
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(position + DirectX::SimpleMath::Vector3::UnitY);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
}
