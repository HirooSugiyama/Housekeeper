/*
�z���G�Փ˔���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#include"pch.h"

#include"DetectSubordinateEnemy.h"

//�O���錾
//����
#include"SubordinateEnemy.h"

//�����蔻��
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Player/ActionStateAttackEnemy.h"
#include"../Bullet/BulletManager.h"

//�֐��̎g�p
#include"Game/PlayScene/PlaySceneCommon/Administrator/Administrator.h"
#include"EnemyCommonFunction.h"


//�z���G�̃X�R�A
const int DetectSubordinateEnemy::SUBORDINATE_ENEMY_SCORE = 100;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
DetectSubordinateEnemy::DetectSubordinateEnemy()
	:
	mpChackColliderSubordinateEnemy(),
	mEnemySize()
{
}

/*===================================
�f�X�g���N�^
===================================*/
DetectSubordinateEnemy::~DetectSubordinateEnemy()
{
}

/*=======================================================================================================
�G�̉񐔕����������蔻����񂷏���(�z���G)
�����F�e�Ǘ��N���X�̃A�h���X
�Ԃ�l�F�Ȃ�
========================================================================================================*/
void DetectSubordinateEnemy::RoolBulletManagerChackhitSubordinateEnemy(BulletManager* pBulletManager)
{
	for (int i = 0; i < mEnemySize; i++)
	{
		//�����蔻��̏�����ʂ�
		int breaknum = pBulletManager->ChackHitBulletSubordinateEnemy(mpChackColliderSubordinateEnemy[i]);

		//�X�R�A����
		DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(SUBORDINATE_ENEMY_SCORE * breaknum);
	}
}

/*===================================
�u���b�N�Ɣz���G�̏Փ˔���
�����F�u���b�N�̃A�h���X
�Ԃ�l�F�Ȃ�
===================================*/
void DetectSubordinateEnemy::ChackHitBlocklSubordinateEnemy(Block* pBlock)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		//�ړ���ԂłȂ��z���G�����������Ȃ�
		if (mpChackColliderSubordinateEnemy[i]->GetState() != SubordinateEnemyMainState::MOVE)continue;

		//�Փ˔���
		if (pC.Intersect(pBlock->GetBoxModel()->GetAABBCollider(),
			mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{
			//�u���b�N��j�󂷂�
			pBlock->SelfDestroy();

			//�G�t�F�N�g�̐ݒ�
			EnemyCommonFunction::SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
		}
	}
}

/*===================================
�v���C���[�Ɣz���G�̏Փ˔���
�����F�v���C���[�̃A�h���X
�Ԃ�l�F�ڐG�t���O
===================================*/
bool DetectSubordinateEnemy::ChackHitPlayerSubordinateEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		if (mpChackColliderSubordinateEnemy[i]->GetStateMove()->GetState() == SubordinateEnemyMoveState::STAND)//������Ԃ�								
		{
			if (pPlayer->GetPlayerState() == ePlayerState::WALK)//�v���C����������ԂȂ��
			{
				//��ԕύX����
				mpChackColliderSubordinateEnemy[i]->GetStateMove()->GetStand()->SetStandIntervalActiveFlag(true);
			}
			continue;
		}

		//�ړ���ԂłȂ��z���G�����������Ȃ�
		if (mpChackColliderSubordinateEnemy[i]->GetState() != SubordinateEnemyMainState::MOVE)continue;

		//�Փ˔���
		if (pC.Intersect(pPlayer->GetPlayerCollider(),
			mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{
			//�v���C���[�Ƀ_���[�W��^����
			pPlayer->ChangeStateDamage();

			//�g�p���Ă���z���G���~������
			this->AllSubordinateEnemyStop();

			return true;
		}
	}
	return false;
}

/*=======================================
��U����Ԃ̃v���C���[�Ɣz���G�̏Փ˔���
�����F�v���C���[�̃A�h���X
�Ԃ�l�F�Ȃ�
========================================*/
void DetectSubordinateEnemy::ChackHitNormalAttackPlayerSubordinateEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();


	//�I������null������\�������邽�߃`�F�b�N����
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return;
	//�����v���C���[����U����ԂłȂ��Ȃ�Βʂ�Ȃ�
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return;

	for (int i = 0; i < mEnemySize; i++)
	{
		//�ړ���ԂłȂ��z���G�����������Ȃ�
		if (mpChackColliderSubordinateEnemy[i]->GetState() != SubordinateEnemyMainState::MOVE)continue;

		//�Փ˔���
		if (pC.Intersect(pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
			mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{
			//��U���̃_���[�W��^����
			int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

			bool breakjuge = mpChackColliderSubordinateEnemy[i]->Damage(damageNum, mpChackColliderSubordinateEnemy[i]->GetEnemyHP());

			//�����G��|���Ă�����
			if (breakjuge)
			{
				//�X�R�A�𑝂₵��
				DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(SUBORDINATE_ENEMY_SCORE);
			}

			//�G�t�F�N�g��ݒ肷��
			EnemyCommonFunction::SetEnemyEffect(eEffectType::SLASH, mpChackColliderSubordinateEnemy[i]->GetEnemyModel()->GetPosition());
		}
	}
}

/*================================================
�g�p���Ă���z���G�S�Ă��~������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================================*/
void DetectSubordinateEnemy::AllSubordinateEnemyStop()
{
	for (int i = 0; i < mEnemySize; i++)
	{
		mpChackColliderSubordinateEnemy[i]->GetStateMove()->ChangeStateStand();
	}
}

