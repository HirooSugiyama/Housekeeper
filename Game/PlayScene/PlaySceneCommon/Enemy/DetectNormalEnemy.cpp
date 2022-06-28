/*
�ʏ�G�Փ˔���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#include"pch.h"

#include"DetectNormalEnemy.h"
#include"Enemy.h"

//�����蔻��
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Protecter.h"
#include"../Administrator/Administrator.h"
#include"../Administrator/Score.h"
#include"../ObjectModel/BoxModel.h"
#include"../Weapon/WeaponHand.h"
#include"../ObjectModel/SphereModel.h"
#include"../../PlaySceneDefence/DangerousLine.h"
#include"../Bullet/BulletManager.h"
#include"../Player/ActionStateAttackEnemy.h"
#include "EnemyCommonFunction.h"

//�G�̃v���C���[�ߑ��͈�
const float DetectNormalEnemy::ENEMY_CAPTURE_RANGE = 5.f;

//�X�R�A�l
const int DetectNormalEnemy::NORMAL_ENEMY_SCORE = 100;

/*=================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
DetectNormalEnemy::DetectNormalEnemy()
	:
	DetectEnemy(),
	mpChackColliderEnemy{},
	mEnemySize(),
	mBossEnemyUseFlag()
{
}

/*==================================
�f�X�g���N�^
===================================*/
DetectNormalEnemy::~DetectNormalEnemy()
{
}

/*==================================================
�G�̉񐔕����������蔻����񂷏���
�����F�e�Ǘ��N���X�̃A�h���X
�Ԃ�l�F�G�̌��j��
====================================================*/
int DetectNormalEnemy::RoolBulletManagerChackhit(BulletManager* pBulletManager)
{
	//�Ԃ�l�p�ϐ�
	int returnNum = 0;
	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�����蔻��̏�����ʂ�
		int breaknum = pBulletManager->ChackHitBulletEnemy(mpChackColliderEnemy[i]);

		if (!mBossEnemyUseFlag)
		{
			//���j��������������������
			returnNum += breaknum;
		}

		//�X�R�A����
		DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(NORMAL_ENEMY_SCORE * breaknum);
	}
	return returnNum;
}

/*=======================================================================================================
�u���b�N�ƓG�̏Փ˔���֐�
����	�FpBlock(�g�p����u���b�N�̃A�h���X)
�Ԃ�l�F�Ȃ�
========================================================================================================*/
void DetectNormalEnemy::ChackHitBlocklEnemy(Block* pBlock)
{
	//�ȗ����p�ϐ��̐錾
	bool colliderFlag = false;
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�G�̐�������������
	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpChackColliderEnemy[i]->GetEnemyMainState() == EnemyMainState::CREATE_BEFORE)continue;

		//�U����Ԃ̏ꍇ 
		if (mpChackColliderEnemy[i]->GetStateMove()->GetMoveState() == EnemyMoveState::WALL_ATTACK)
		{
			//�U�����Ă���ǂ̏ꍇ�̂ݏ������s��
			if (mpChackColliderEnemy[i]->GetStateMove()->GetFirstHitBlock() == pBlock)
			{
				//�U������
				mpChackColliderEnemy[i]->AttackBlock(pBlock);
			}
		}
		//�U����ԈȊO�̏ꍇ
		else
		{
			//�G�s��State�̓����蔻��ŏՓ˔�������
			colliderFlag = pC.Intersect
			(
				mpChackColliderEnemy[i]->GetStateMove()->GetAABBCollider(),
				pBlock->GetBoxModel()->GetAABBCollider()
			);

			//�������Ă��Ȃ������珈�������Ȃ�
			if (!colliderFlag)continue;

			//�Փ˃t���O�����Ă�
			if (mpChackColliderEnemy[i]->GetStateMove()->GetBlockHitFlag() != EnemyMainStateMove::EnemyBlockHit::HIT)
			{
				mpChackColliderEnemy[i]->GetStateMove()->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::HIT);
			}

			//�ǂ̉������
			mpChackColliderEnemy[i]->AvoidanceBlock(pBlock);
		}
	}
}

/*==================================================
�v���C���[�ƓG�̏Փ˔���֐�
�����F�v���C���[�̃A�h���X
�Ԃ�l�F�ڐG�t���O
====================================================*/
bool DetectNormalEnemy::ChackHitPlayerEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�v���C���[���_���[�W��ԂȂ珈�������Ȃ�
	if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) return false;

	//�G�̐�������������
	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(), pPlayer->GetPlayerCollider()))
		{
			//�v���C���[�Ƀ_���[�W��^����
			pPlayer->ChangeStateDamage();

			return true;
		}
	}

	return false;
}

/*===================================================
�v���C���[�U�����̃v���C���[�ƓG�̏Փ˔���֐�
�����F�v���C���[�̃A�h���X
�Ԃ�l�F���j��
====================================================*/
int DetectNormalEnemy::ChackHitNormalAttackPlayerEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�I������null������\�������邽�߃`�F�b�N����
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return false;
	//�����v���C���[����U����ԂłȂ��Ȃ�Βʂ�Ȃ�
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return false;

	//�Ԃ�l�p�ϐ��̐錾
	int returnNum{ 0 };

	//�G�̐�������������
	for (int i = 0; i < mEnemySize; i++)
	{

		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider()))
		{

			//��U���̃_���[�W��^����
			int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

			bool breakjuge = mpChackColliderEnemy[i]->Damage(damageNum, mpChackColliderEnemy[i]->GetEnemyHP());

			//�����G��|���Ă�����
			if (breakjuge)
			{
				//���j���ǉ�
				returnNum++;

				//�X�R�A�𑝂₵��
				DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(NORMAL_ENEMY_SCORE);
			}
			//�|���ĂȂ�������_���[�W�l��\������
			else
			{
				//�G�t�F�N�g�����Z�b�g����
				mpChackColliderEnemy[i]->ResetNumberEffect();

				mpChackColliderEnemy[i]->CreateNumberEffect(mpChackColliderEnemy[i]->GetEnemyDamage());
			}

			//�G�t�F�N�g��ݒ肷��
			EnemyCommonFunction::SetEnemyEffect(eEffectType::SLASH, mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition());

			//�m�b�N�o�b�N�̕������Z�o����
			DirectX::SimpleMath::Vector3 knockBackVelocity =
				pPlayer->GetAttackEnemy()->GetHand()->GetColliderPosition() - pPlayer->GetPlayerModel()->GetPosition();

			//�_���[�W��ԂɈڍs
			mpChackColliderEnemy[i]->ChangeStateDamage();
			//�ŏ��̏�Ԃ͔������
			mpChackColliderEnemy[i]->GetStateDamage()->ChangeStateKnockBack();
			mpChackColliderEnemy[i]->GetStateDamage()->MoveVectorScaling(knockBackVelocity);

			//�ǂ�������ԂƂ���
			mpChackColliderEnemy[i]->GetStateMove()->SetChasePlayerFlag(true);
		}
	}
	return returnNum;
}

/*===================================================
���_�ƓG�̏Փ˔���֐�
�����F���_�̃A�h���X
�Ԃ�l�F�Ȃ�
====================================================*/
void DetectNormalEnemy::ChackHitProtecterEnemy(Protecter* pProtecter)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�G�̐�������������
	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�������Ă����珈��������
		if (
			pC.Intersect(
				mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(),
				pProtecter->GetProtecterModel()->GetAABBCollider())
			)
		{
			//�G��j�󂷂�
			mpChackColliderEnemy[i]->SelfDestroy();


			//�Ƃ̑ϋv�l�����炷
			pProtecter->SetDamageFlag(true);
		}
	}
}

/*======================================================================
�n��I�u�W�F�N�g�ƓG�̓����蔻��
�����F�n��I�u�W�F�N�g�Ǘ��N���X���̓����蔻��ЂƂ̃A�h���X
�Ԃ�l�F�Ȃ�
=======================================================================*/
void DetectNormalEnemy::ChackHitGroundObjectEnemy(AABB* pObjectCollider)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(),	//�G�̓����蔻��
			pObjectCollider)												//�n��I�u�W�F�N�g�̓����蔻��
			)								
		{
			//���]������
			mpChackColliderEnemy[i]->GetStateMove()->ReverseAngle();
		}
	}
}

/*======================================================================
��ƓG�̓����蔻��
�����F��̓����蔻��A�h���X
�Ԃ�l�F�Ȃ�
=======================================================================*/
void DetectNormalEnemy::ChackHitWallNormalEnemy(AABB* pWallCollider)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			mpChackColliderEnemy[i]->GetEnemyModel()->GetAABBCollider(),	//�G�̓����蔻��
			pWallCollider))													//�n��I�u�W�F�N�g�̓����蔻��
		{
			//���]������
			mpChackColliderEnemy[i]->GetStateMove()->ReverseAngle();
		}
	}
}

/*========================================
�댯�M�����C���ƓG�̓����蔻��
�����F�댯�M�����C���̃A�h���X
�Ԃ�l�F���C���ڐG�t���O
=========================================*/
bool DetectNormalEnemy::ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine)
{
	//�ȗ����p�ϐ��̐錾
	float enemyPositionZ = 0.f, linePositionZ = 0.f;


	//��������p�t���O�̐錾
	bool effectMoveFlag = false;

	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpChackColliderEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//���W��ݒ肷��
		enemyPositionZ = mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition().z;
		linePositionZ = pDangerousLine->GetLinePositionZ();

		//�����G�����C�����Ƒ��ɂ�����t���O�����Ă�
		if (enemyPositionZ > linePositionZ)
		{
			effectMoveFlag = true;
			//���鐔�͊֌W�Ȃ��̂Ŕ�����
			break;
		}
	}

	return effectMoveFlag;
}

/*========================================
�ΏۂƓG�̋�������
�����F�Ώۂ̍��W
�Ԃ�l�F�Ȃ�
=========================================*/
void DetectNormalEnemy::ChackDistanceTargetEnemy(const DirectX::SimpleMath::Vector3& position)
{
	//�Z�o�p�ϐ�
	float distance(0);

	//�����x�N�g���ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3 distanceVelocity(DirectX::SimpleMath::Vector3::Zero);

	for (int i = 0; i < mEnemySize; i++)
	{
		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (!mpChackColliderEnemy[i]->GetStateMove()->GetChasePlayerFlag())continue;

		//�������v������
		distance = std::sqrtf((std::abs(position.x - mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition().x)) * 2 +
			(std::abs(position.z - mpChackColliderEnemy[i]->GetEnemyModel()->GetPosition().z)) * 2);

		//��苗���ɂ��炸�A�ǂ�������ԂȂ�
		if (distance > ENEMY_CAPTURE_RANGE)
		{
			//�ʏ�ɖ߂�
			mpChackColliderEnemy[i]->GetStateMove()->SetChasePlayerFlag(false);
		}
	}
}
