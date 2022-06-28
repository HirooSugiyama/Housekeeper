/*
�G�Ǘ��N���X
*/

#include<pch.h>

#include "BossEnemyManager.h"


//�O���錾
#include"../../Effect/Effect.h"

//�����蔻��
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Protecter.h"
#include"../Administrator/Administrator.h"

//�����蔻��̍ۂɊ֐����g�p
#include"../Administrator/Score.h"
#include"../ObjectModel/BoxModel.h"
#include"../Weapon/WeaponHand.h"
#include"../ObjectModel/SphereModel.h"
#include"../../PlaySceneDefence/DangerousLine.h"

//�񋓌^�̎g�p
#include"../Player/ActionStateAttackEnemy.h"

//�G�t�F�N�g�̎擾
#include"../../Effect/EffectManager.h"

#include"../Bullet/BulletManager.h"


//�����T�C�Y
const int BossEnemyManager::ENEMY_INIT_SIZE = 100;

//���g�p�̓G�̏o�����W
const DirectX::SimpleMath::Vector3 BossEnemyManager::NOT_SET_ENEMY_POSITION(-10.f, -10.f, -10.f);


//�����g�嗦
const DirectX::SimpleMath::Vector3 BossEnemyManager::ENEMY_INIT_SCALE(1.f, 1.f, 1.f);

//�G�̍U����
const int BossEnemyManager::ENEMY_ATTACK_NUM = 1;


//�X�R�A�l
const int BossEnemyManager::ENEMY_SCORE = 100;

//�G�t�F�N�g�̏o����������W
const DirectX::SimpleMath::Vector3 BossEnemyManager::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);

//�G�̃v���C���[�ߑ��͈�
const float BossEnemyManager::ENEMY_CAPTURE_RANGE = 5.f;

//���]��
const int BossEnemyManager::REVERSE_NUM = 2;

//BOSS�������̒ʏ�G��������
const int BossEnemyManager::ENEMY_ADDITIONAL_CAPACITY = 20;

//�z���G�����͈�
const int BossEnemyManager::SUBORDINATE_ENEMY_CREATE_RANGE = 70;


//�{�X�G�̔z���G������
const int BossEnemyManager::SUBORDINATE_ENEMY_CREATE_NUM = 5;

//�{�X�G�̒ʏ�G������
const int BossEnemyManager::NORNAML_ENEMY_CREATE_NUM = 1;


//�z���G�̐�����
const int BossEnemyManager::SUBORDINATE_ENEMY_ARIVE_NUM = 3;


//�{�X�G�̒ʏ�G�������̃t�F�[�Y�ԍ�
const int BossEnemyManager::NORMAL_ENEMY_CREATE_PHASE = 1;

/*===================================
�R���X�g���N�^
===================================*/
BossEnemyManager::BossEnemyManager()
	:
	mpBossEnemy(),
	mEnemyAppearanceInterval(0),
	mpEnemyCall(nullptr),
	mpAdministrator(nullptr),
	mMaxEnemySpawnPositionZ(0),
	mLoadEnemyFileName("none"),
	mNowPhaseNum(0),
	mMaxPhaseNum(0),
	mNowEnemyBreakNum(),
	mBossEnemyUseFlag(false)
{
	//�Ăяo���N���X���`
	mpEnemyCall = std::make_unique<EnemyCall>();

	mpBossEnemy = std::make_unique<BossEnemy>();
}

/*=================================
�f�X�g���N�^
===================================*/
BossEnemyManager::~BossEnemyManager()
{
}
/*=========================================================
����������
�����F�J�����ւ̃A�h���X�A�Ǘ��҃N���X�̃A�h���X
=========================================================*/
void BossEnemyManager::Initialize(CameraBase* camera, Administrator* pAdministrator, Player* pPlayer)
{
	//�G�̓ǂݍ���
	this->LoadFile(mLoadEnemyFileName);

	//�A�h���X�ۑ�
	mpAdministrator = pAdministrator;

	//���W�̃A�h���X�ۑ�
	mpBossEnemy->GetStateMove()->SetSavePlayerPointer(pPlayer->GetPlayerPositionAddress());

	//�J�����̃A�h���X�̕ۑ�
	mpBossEnemy->SaveCameraPointer(camera);
}

/*===================================
�X�V����
===================================*/
void BossEnemyManager::Update()
{


	if (mBossEnemyUseFlag)
	{
		//�{�X�G�̍X�V����
		if (mpBossEnemy->GetMovePhaseNumber() == mNowPhaseNum &&
			mpBossEnemy->GetState() == BossEnemyMainState::CREATE_BEFORE)
		{
			//�o����Ԃ�
			mpBossEnemy->GetStateCreateBefore()->ChangeState();
		}
		//�{�X�G�̍X�V����
		mpBossEnemy->Update();
	}
}

/*=================================
�`�揈��
===================================*/
void BossEnemyManager::Draw()
{
	if (mBossEnemyUseFlag)
	{
		//�{�X�G�̕`�揈��
		mpBossEnemy->Draw();
	}
}

/*=================================
�I������
===================================*/
void BossEnemyManager::Finalize()
{
	mpBossEnemy->Finalize();
}

/*=======================================================================================================
�G�̉񐔕����������蔻����񂷏���(�{�X�G)
�����F�e�Ǘ��N���X�̃A�h���X
========================================================================================================*/
void BossEnemyManager::RoolBulletManagerChackhitBossEnemy(BulletManager* pBulletManager)
{
	//�{�X���g�p���Ă��Ȃ��Ƃ��͏�����ʂ��Ȃ�
	if (!mpBossEnemy->GetUseFlag())return;

	//���j��������������������
	int breaknum = pBulletManager->ChackHitBulletBossEnemy(mpBossEnemy.get());

	//���j��������������������
	mNowEnemyBreakNum += breaknum;

	//�X�R�A����
	mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE * breaknum);

}

/*=================================
�ǂݍ��ރt�@�C�������쐬
�����F�X�e�[�W�ԍ�
�Ԃ�l�F�t�@�C����
===================================*/
std::string BossEnemyManager::CreateLoadEnemyFileName(std::string const& stagenum)
{
	std::string filetop = "Resources/CSV/Enemy",
		filebottom = ".csv",
		filename = "none";

	filename = filetop + stagenum + filebottom;

	return filename;

}


/*==========================================
�S�Ă̓G�����S�������Ƃ��m�F����t���O
==========================================*/
bool BossEnemyManager::AllEnemyDeathFlag()
{
	//���݂̃t�F�[�Y���ő�t�F�[�Y�o�Ȃ��Ȃ�Ώ�����ʂ��Ȃ�
	if (mNowPhaseNum != mMaxPhaseNum)
	{
		return false;
	}
	if (mBossEnemyUseFlag)
	{
		if (mpBossEnemy->GetUseFlag())
		{
			return false;
		}
	}

	//�����ɗ���==�S�Ă̓G�����g�p��Ԃ̏ꍇ
	return true;
}

/*==================================
�����Ă���G����Ăɔ��j������
===================================*/
void BossEnemyManager::ExplosionSimultaneousEnemy()
{
	if (mpBossEnemy->GetUseFlag())
	{
		//�G�t�F�N�g��ݒ肷��
		this->SetEnemyEffect(eEffectType::BOMB, mpBossEnemy->GetEnemyModel()->GetPosition());
		mpBossEnemy->SelfDestroy();
	}
}

/*==================================================
�u���b�N�ƃ{�X�G�̏Փ˔���
�����F�u���b�N�̃A�h���X
====================================================*/
void BossEnemyManager::ChackHitBlocklBossEnemy(Block* pBlock)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�Փ˔���
	if (pC.Intersect(pBlock->GetBoxModel()->GetAABBCollider(),
		mpBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//�u���b�N��j�󂷂�
		pBlock->SelfDestroy();

		//�G�t�F�N�g�̐ݒ�
		this->SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
	}
}

/*==================================================
�v���C���[�ƃ{�X�G�̏Փ˔���
�����F�v���C���[�̃A�h���X
====================================================*/
void BossEnemyManager::ChackHitPlayerBossEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�v���C���[���_���[�W��ԂȂ珈�������Ȃ�
	if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) return;

	//�Փ˔���
	if (pC.Intersect(pPlayer->GetPlayerCollider(),
		mpBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//�v���C���[�Ƀ_���[�W��^����
		pPlayer->ChangeStateDamage();
	}
}

/*==================================================
��U����Ԃ̃v���C���[�ƃ{�X�G�̏Փ˔���
�����F�v���C���[�̃A�h���X
====================================================*/
void BossEnemyManager::ChackHitNormalAttackPlayerBossEnemy(Player* pPlayer)
{
	Collider& pC = Collider::GetColliderInstance();

	//�I������null������\�������邽�߃`�F�b�N����
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return;
	//�����v���C���[����U����ԂłȂ��Ȃ�Βʂ�Ȃ�
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return;

	//�����Ԃ̏ꍇ���U�����󂯂Ȃ�
	if (mpBossEnemy->GetStateMove()->GetMoveState() == BossEnemyMoveState::ESCAPE)return;

	//�������Ă����珈��������
	if (pC.Intersect(
		pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
		mpBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//��U���̃_���[�W��^����
		int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

		bool breakjuge = mpBossEnemy->Damage(damageNum, mpBossEnemy->GetEnemyHP());

		//�����G��|���Ă�����
		if (breakjuge)
		{
			//���j���ǉ�
			mNowEnemyBreakNum++;

			//�X�R�A�𑝂₵��
			mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE);
		}

		//������ԂƂ���
		mpBossEnemy->GetStateMove()->ChangeStateEscape();

		//�G�t�F�N�g��ݒ肷��
		this->SetEnemyEffect(eEffectType::SLASH, mpBossEnemy->GetEnemyModel()->GetPosition());

	}
}

/*==================================================
��ƃ{�X�G�̏Փ˔���
�����F��̏Փ˔���A�h���X
====================================================*/
void BossEnemyManager::ChackHitWallBossEnemy(AABB* pWallCollider)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();
	
	//�������Ă����珈��������
	if (pC.Intersect(
		mpBossEnemy->GetEnemyModel()->GetAABBCollider(),	//�G�̓����蔻��
		pWallCollider))										//�n��I�u�W�F�N�g�̓����蔻��
	{
		//Todo:��~������
		DirectX::SimpleMath::Vector3 shiftPosition = mpBossEnemy->GetEnemyModel()->GetPosition();
		shiftPosition.x = pWallCollider->mMin.x;
		mpBossEnemy->GetEnemyModel()->SetPosition(shiftPosition);
	}
}

/*===================================
�{�X�͈͂ƃv���C���[�̏Փ˔���
�����F�v���C���[�̃A�h���X
===================================*/
void BossEnemyManager::ChackHitPlayerBossEnemyArea(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�ړ���ԈȊO�Ȃ珈�������Ȃ�
	if (mpBossEnemy->GetState() != BossEnemyMainState::MOVE)return;

	//�Փ˔���
	if (pC.Intersect(
		mpBossEnemy->GetPlayerRecognitionRangeCollider(),
		pPlayer->GetPlayerCollider()))
	{

		//�z���G����������
		mpBossEnemy->ChangeStateCreate();

		//�����t���O�������Ă��Ȃ������猚�Ă�
		if (!mpBossEnemy->GetActiveFlag())
		{
			mpBossEnemy->SetActiveFlag(true);
		}
	}
}

/*===================================
�t�@�C����������擾����:private
�����F�t�@�C���p�X�A�J�����ւ̃A�h���X
===================================*/
void BossEnemyManager::LoadFile(std::string filepath)
{
	//������
	DirectX::SimpleMath::Vector3 pos= NOT_SET_ENEMY_POSITION;
	int phasenum = 0;


	//���ǂݍ���
	mpEnemyCall->LoadInfo(filepath);

	//BOSS��������
	mBossEnemyUseFlag = this->CreateBoss();

	//�s�v�ɂȂ����̂ō폜
	mpEnemyCall->Reset();
}

/*======================================================================
�{�X�G��������
========================================================================*/
bool BossEnemyManager::CreateBoss()
{
	if (mpEnemyCall->GetBossEnemyStructer().mPhaseNumber == 0)return false;

	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 pos = NOT_SET_ENEMY_POSITION;
	int phasenum = 0;

	//BOSS����
	pos = mpEnemyCall->GetBossEnemyStructer().mVectorESPosition;
	phasenum = mpEnemyCall->GetBossEnemyStructer().mPhaseNumber;
	mpBossEnemy->SetMovePhaseNumber(phasenum);
	mpBossEnemy->Initialize(pos);

	return true;
}


/*======================================================================
�G�t�F�N�g��ݒ肷��:private
�����F�G�t�F�N�g�̎�ށA�G�̍��W�A
		�G�̗v�f�ԍ��A�G�t�F�N�g�t���O�����Ă邩(true�F���Ă�)
========================================================================*/
void BossEnemyManager::SetEnemyEffect(eEffectType const& type, DirectX::SimpleMath::Vector3 const& pos)
{
	//�G�t�F�N�g�}�l�[�W���[�̎擾
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(pos + EFFECT_SHIFT_POSITION);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
}

/*==================================================
���W����:private
�����F��ƂȂ���W
�Ԃ�l�F�������W
===================================================*/
DirectX::SimpleMath::Vector3 BossEnemyManager::CreatePosition(DirectX::SimpleMath::Vector3 const& position)
{
	//int�^�ɖ߂����߈ꎞ�I��10�{����
	DirectX::SimpleMath::Vector3 castPosition = position * 10.f;

	// �񌈒�I�ȗ���������ŃV�[�h�����@�𐶐�
	std::random_device rnd;
	//�����Z���k�c�C�X�^�[��32�r�b�g�ŁA�����͏����V�[�h
	std::mt19937 mt(rnd());
	//������U��
	std::uniform_int_distribution<> randX
	(
		castPosition.x - SUBORDINATE_ENEMY_CREATE_RANGE,
		castPosition.x + SUBORDINATE_ENEMY_CREATE_RANGE
	);

	std::uniform_int_distribution<> randZ
	(
		castPosition.z - SUBORDINATE_ENEMY_CREATE_RANGE,
		castPosition.z + SUBORDINATE_ENEMY_CREATE_RANGE
	);

	//���W�ݒ�
	castPosition.x = randX(mt);
	castPosition.z = randZ(mt);

	//float�ϊ�(/10)
	castPosition /= 10.f;
	castPosition.y = position.y;

	//�X�e�[�W�[�̏���
	if (castPosition.x > Utility::FIELD_MAX_SIZE_X)
	{
		castPosition.x = Utility::FIELD_MAX_SIZE_X;
	}
	else if (castPosition.x < Utility::FIELD_MIN_SIZE_X)
	{
		castPosition.x = Utility::FIELD_MIN_SIZE_X;
	}

	if (castPosition.z > Utility::FIELD_MAX_SIZE_Z)
	{
		castPosition.z = Utility::FIELD_MAX_SIZE_Z;
	}
	else if (castPosition.z < Utility::FIELD_MIN_SIZE_Z)
	{
		castPosition.z = Utility::FIELD_MIN_SIZE_Z;
	}

	return castPosition;
}
