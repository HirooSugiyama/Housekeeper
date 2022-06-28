/*
�z���G�Փ˔���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#include"pch.h"

#include"DetectBossEnemy.h"

//�O���錾
//����
#include"BossEnemy.h"

//�����蔻��
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Player/ActionStateAttackEnemy.h"
#include"../Bullet/BulletManager.h"

//�֐��̎g�p
#include"Game/PlayScene/PlaySceneCommon/Administrator/Administrator.h"
#include"EnemyCommonFunction.h"


//�z���G�̃X�R�A
const int DetectBossEnemy::BOSS_ENEMY_SCORE = 100;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
DetectBossEnemy::DetectBossEnemy()
	:
	mpChackColliderBossEnemy()
{
}

/*===================================
�f�X�g���N�^
===================================*/
DetectBossEnemy::~DetectBossEnemy()
{
}

/*=======================================================================================================
�G�̉񐔕����������蔻����񂷏���(�{�X�G)
�����F�e�Ǘ��N���X�̃A�h���X
�Ԃ�l�F���j�t���O
========================================================================================================*/
bool DetectBossEnemy::RoolBulletManagerChackhitBossEnemy(BulletManager* pBulletManager)
{
	//�{�X���g�p���Ă��Ȃ��Ƃ��͏�����ʂ��Ȃ�
	if (!mpChackColliderBossEnemy->GetUseFlag())return false;

	//���j��������������������
	bool breakflag = pBulletManager->ChackHitBulletBossEnemy(mpChackColliderBossEnemy);

	//�X�R�A����
	if (breakflag)
	{
		DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(BOSS_ENEMY_SCORE);
	}

	return breakflag;
}

/*==================================================
�u���b�N�ƃ{�X�G�̏Փ˔���
�����F�u���b�N�̃A�h���X
�Ԃ�l�F�Ȃ�
====================================================*/
void DetectBossEnemy::ChackHitBlocklBossEnemy(Block* pBlock)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�Փ˔���
	if (pC.Intersect(pBlock->GetBoxModel()->GetAABBCollider(),
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//�u���b�N��j�󂷂�
		pBlock->SelfDestroy();

		//�G�t�F�N�g�̐ݒ�
		EnemyCommonFunction::SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
	}
}

/*==================================================
�v���C���[�ƃ{�X�G�̏Փ˔���
�����F�v���C���[�̃A�h���X
�Ԃ�l�F�Փ˃t���O
====================================================*/
bool DetectBossEnemy::ChackHitPlayerBossEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//���g�p���͏��������Ȃ�
	if (mpChackColliderBossEnemy == nullptr)return false;

	//�v���C���[���_���[�W��ԂȂ珈�������Ȃ�
	if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) return false;

	//�Փ˔���
	if (pC.Intersect(pPlayer->GetPlayerCollider(),
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//�v���C���[�Ƀ_���[�W��^����
		pPlayer->ChangeStateDamage();

		return true;
	}

	return false;
}

/*==================================================
��U����Ԃ̃v���C���[�ƃ{�X�G�̏Փ˔���
�����F�v���C���[�̃A�h���X
�Ԃ�l�F���j�t���O
====================================================*/
bool DetectBossEnemy::ChackHitNormalAttackPlayerBossEnemy(Player* pPlayer)
{
	Collider& pC = Collider::GetColliderInstance();

	//�I������null������\�������邽�߃`�F�b�N����
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return false;
	if (mpChackColliderBossEnemy == nullptr)return false;

	//�����v���C���[����U����ԂłȂ��Ȃ�Βʂ�Ȃ�
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return false;

	//�����Ԃ̏ꍇ���U�����󂯂Ȃ�
	if (mpChackColliderBossEnemy->GetStateMove()->GetMoveState() == BossEnemyMoveState::ESCAPE)return false;

	//�������Ă����珈��������
	if (pC.Intersect(
		pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//��U���̃_���[�W��^����
		int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

		bool breakjuge = mpChackColliderBossEnemy->Damage(damageNum, mpChackColliderBossEnemy->GetEnemyHP());

		//������ԂƂ���
		mpChackColliderBossEnemy->GetStateMove()->ChangeStateEscape();

		//�G�t�F�N�g��ݒ肷��
		EnemyCommonFunction::SetEnemyEffect(eEffectType::SLASH, mpChackColliderBossEnemy->GetEnemyModel()->GetPosition());

		//�����G��|���Ă�����
		if (breakjuge)
		{
			//�X�R�A�𑝂₵��
			DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(BOSS_ENEMY_SCORE);

			return true;
		}

	}
	return false;
}

/*==================================================
��ƃ{�X�G�̏Փ˔���
�����F��̏Փ˔���A�h���X
�Ԃ�l�F�Ȃ�
====================================================*/
void DetectBossEnemy::ChackHitWallBossEnemy(AABB* pWallCollider)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//���g�p���͏��������Ȃ�
	if (mpChackColliderBossEnemy == nullptr)return;

	//�������Ă����珈��������
	if (pC.Intersect(
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider(),	//�G�̓����蔻��
		pWallCollider))										//�n��I�u�W�F�N�g�̓����蔻��
	{
		//Todo:��~������
		DirectX::SimpleMath::Vector3 shiftPosition = mpChackColliderBossEnemy->GetEnemyModel()->GetPosition();
		shiftPosition.x = pWallCollider->mMin.x;
		mpChackColliderBossEnemy->GetEnemyModel()->SetPosition(shiftPosition);
	}
}

/*===================================
�{�X�͈͂ƃv���C���[�̏Փ˔���
�����F�v���C���[�̃A�h���X
�Ԃ�l�F�Ȃ�
===================================*/
void DetectBossEnemy::ChackHitPlayerBossEnemyArea(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//���g�p���͏��������Ȃ�
	if (mpChackColliderBossEnemy == nullptr)return;

	//�ړ���ԈȊO�Ȃ珈�������Ȃ�
	if (mpChackColliderBossEnemy->GetState() != BossEnemyMainState::MOVE)return;

	//�Փ˔���
	if (pC.Intersect(
		mpChackColliderBossEnemy->GetPlayerRecognitionRangeCollider(),
		pPlayer->GetPlayerCollider()))
	{

		//�z���G����������
		mpChackColliderBossEnemy->ChangeStateCreate();

		//�����t���O�������Ă��Ȃ������猚�Ă�
		if (!mpChackColliderBossEnemy->GetActiveFlag())
		{
			mpChackColliderBossEnemy->SetActiveFlag(true);
		}
	}
}
