/*
��������e�̈ړ�����
�쐬�ҁF���R
�쐬���F2021/10/16
*/

#include"pch.h"
#include "BulletStateExplosion.h"

//�O���錾
#include"Bullet.h"

//�֐��̎g�p
#include"../ObjectModel/SphereModel.h"
#include"../Enemy/Enemy.h"
#include"../Enemy/BossEnemy.h"
#include"../Enemy/SubordinateEnemy.h"

//�G�t�F�N�g�̎擾
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//�d�͒萔�̎g�p
#include"../../PlaySceneDefence/Gravity.h"

//�d�͒萔
const float BulletStateExplosion::GRAVITY = Gravity::mGravityConstant;

//�������x
const float BulletStateExplosion::FIRST_VELOCITY = 0.3f;

//�ŏ��̍���
const float BulletStateExplosion::FIRST_HEIGHT = 1.f;


//�G�t�F�N�g���o����������W
const DirectX::SimpleMath::Vector3 BulletStateExplosion::EFFECT_SHIFT_POSITION(0.f, 2.5f, 0.f);

/*==================
�R���X�g���N�^
�����F�Ȃ�
==================*/
BulletStateExplosion::BulletStateExplosion()
	:
	BulletStateBase(),
	mBulletVelocity(FIRST_VELOCITY),
	mBulletHeight(FIRST_HEIGHT)
{
}

/*======================================
�ړ�����
�����F�Ȃ�
�Ԃ�l�F������͖��g�p(��State��Ŏg�p)
=======================================*/
bool BulletStateExplosion::Move()
{
	//���������t���O�������Ă�����
	if (BulletStateBase::GetBullet()->GetExplosionFlag())
	{
		//�G�t�F�N�g�𔭐�������
		//�G�t�F�N�g�}�l�[�W���[�̎擾
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::BOMB);
		effect->SetPosition(BulletStateBase::GetBullet()->GetBulletModel()->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetScale(effect->GetScale());
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		//���g�p��ԂƂ���
		this->Reset();
		return true;
	}


	mBulletVelocity -= GRAVITY;
	mBulletHeight += mBulletVelocity;

	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//���W�֔��f
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	DirectX::SimpleMath::Vector3 position = BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	position.y = mBulletHeight;

	BulletStateBase::GetBullet()->GetBulletModel()->SetPosition(position);
	

	//�n�ʂ�艺�ɍs������
	if (position.y <= 0.f)
	{
		//�����t���O�����Ă�
		BulletStateBase::GetBullet()->SetExplosionFlag(true);
		BulletStateBase::GetBullet()->SetDoubleCollider();
	}

	return false;	
}

/*======================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=======================================*/
void BulletStateExplosion::Draw()
{

}


/*=================================
�e�Փˎ��̒ʏ�G�̏���
�����F�ʏ�G�̃|�C���^
�Ԃ�l�F�G�t�F�N�g�̎��
===================================*/
eEffectType BulletStateExplosion::HitNormalEnemy(Enemy* pEnemy)
{
	//�Փ˔���g��
	BulletStateBase::GetBullet()->SetDoubleCollider();

	//�m�b�N�o�b�N�̕������Z�o����
	DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetEnemyModel()->GetPosition() -
		BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	knockBackVelocity.y = 0.f;

	//��Ԃ��_���[�W��ԂƂ���
	pEnemy->ChangeStateDamage();
	pEnemy->GetStateDamage()->ChangeStateKnockBack();
	pEnemy->GetStateDamage()->MoveVectorScaling(knockBackVelocity);

	//�G�t�F�N�g�̃^�C�v��ݒ�
	return eEffectType::BOMB;
}
/*=================================
�e�Փˎ��̃{�X�G�̏���
�����F�{�X�G�̃|�C���^
�Ԃ�l�F�G�t�F�N�g�̎��
===================================*/
eEffectType BulletStateExplosion::HitBossEnemy(BossEnemy* pEnemy)
{
	//�Փ˔���g��
	BulletStateBase::GetBullet()->SetDoubleCollider();

	//�m�b�N�o�b�N�̕������Z�o����
	DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetEnemyModel()->GetPosition() -
		BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	knockBackVelocity.y = 0.f;

	//��Ԃ��_���[�W��ԂƂ���
	pEnemy->ChangeStateMove();
	pEnemy->GetStateMove()->ChangeStateEscape();

	//�G�t�F�N�g�̃^�C�v��ݒ�
	return eEffectType::BOMB;
}
/*=================================
�e�Փˎ��̔z���G�̏���
�����F�z���G�̃|�C���^
�Ԃ�l�F�G�t�F�N�g�̎��
===================================*/
eEffectType BulletStateExplosion::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//�Փ˔���g��
	BulletStateBase::GetBullet()->SetDoubleCollider();

	//�m�b�N�o�b�N�̕������Z�o����
	DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetEnemyModel()->GetPosition() -
		BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	knockBackVelocity.y = 0.f;

	//�G�t�F�N�g�̃^�C�v��ݒ�
	return eEffectType::BOMB;
}


/*======================================
���Z�b�g����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=======================================*/
void BulletStateExplosion::Reset()
{
	mBulletVelocity = FIRST_VELOCITY;
	mBulletHeight = FIRST_HEIGHT;
}