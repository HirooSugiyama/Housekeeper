/*
�G�Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include<pch.h>

#include "EnemyManager.h"


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
#include"../Bullet/BulletManager.h"

//�񋓌^�̎g�p
#include"../Player/ActionStateAttackEnemy.h"

//�G�t�F�N�g�̎擾
#include"../../Effect/EffectManager.h"
#include"EnemyCommonFunction.h"


//�����T�C�Y
const int EnemyManager::ENEMY_INIT_SIZE = 100;

//���g�p�̓G�̏o�����W
const DirectX::SimpleMath::Vector3 EnemyManager::NOT_SET_ENEMY_POSITION(-10.f, -10.f, -10.f);


//�����g�嗦
const DirectX::SimpleMath::Vector3 EnemyManager::ENEMY_INIT_SCALE(1.f, 1.f, 1.f);


//BOSS�������̒ʏ�G��������
const int EnemyManager::ENEMY_ADDITIONAL_CAPACITY = 20;

//�z���G�����͈�
const int EnemyManager::SUBORDINATE_ENEMY_CREATE_RANGE = 70;


//�{�X�G�̔z���G������
const int EnemyManager::SUBORDINATE_ENEMY_CREATE_NUM = 5;

//�{�X�G�̒ʏ�G������
const int EnemyManager::NORNAML_ENEMY_CREATE_NUM = 1;


//�z���G�̐�����
const int EnemyManager::SUBORDINATE_ENEMY_ARIVE_NUM = 3;


//�{�X�G�̒ʏ�G�������̃t�F�[�Y�ԍ�
const int EnemyManager::NORMAL_ENEMY_CREATE_PHASE = 1;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
EnemyManager::EnemyManager()
	:
	mpEnemy{},
	mpBossEnemy(),
	mpSubordinateEnemy{},
	mpEnemyCall(nullptr),
	mpAdministrator(nullptr),
	mMaxEnemySpawnPositionZ(0),
	mLoadEnemyFileName("none"),
	mNowPhaseNum(0),
	mMaxPhaseNum(0),
	mNowEnemyBreakNum(),
	mBossEnemyUseFlag(false)
{
	//�T�C�Y���������m�ۗp�ő吔�ɐݒ肷��
	mpEnemy.resize(ENEMY_INIT_SIZE);

	//�Ăяo���N���X���`
	mpEnemyCall = std::make_unique<EnemyCall>();


	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		mpEnemy[i] = std::make_unique<Enemy>();
	}
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		mpSubordinateEnemy[i] = std::make_unique<SubordinateEnemy>();
	}
	mpBossEnemy = std::make_unique<BossEnemy>();

}

/*=================================
�f�X�g���N�^
===================================*/
EnemyManager::~EnemyManager()
{
}
/*=========================================================
����������
�����F�J�����ւ̃A�h���X�A�Ǘ��҃N���X�̃A�h���X�A�v���C���[�̃A�h���X
�Ԃ�l�F�Ȃ�
=========================================================*/
void EnemyManager::Initialize(CameraBase* camera, Administrator* pAdministrator, Player* pPlayer)
{
	//�G�̓ǂݍ���
	this->LoadFile(mLoadEnemyFileName);

	//�A�h���X�ۑ�
	mpAdministrator = pAdministrator;

	//���W�̃A�h���X�ۑ�
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mpEnemy[i]->GetStateMove()->SetChasePlayerPositon(pPlayer->GetPlayerPositionAddress());
	}
	mpBossEnemy->GetStateMove()->SetSavePlayerPointer(pPlayer->GetPlayerPositionAddress());
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		mpSubordinateEnemy[i]->GetStateMove()->GetWalk()->SetSavePlayerPointer(pPlayer->GetPlayerPositionAddress());
	}

	//�J�����̃A�h���X�̕ۑ�
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mpEnemy[i]->SaveCameraPointer(camera);
	}
	mpBossEnemy->SaveCameraPointer(camera);
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		mpSubordinateEnemy[i]->SaveCameraPointer(camera);
	}
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::Update()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		//�g�p���̂�
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݏ�����ʂ�
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum) continue;

		//��O�����̏ꍇ��������ʂ��Ȃ�
		if (mpEnemy[i]->GetMovePhaseNumber() == Utility::EXCEPTION_NUM) continue;

		//�����ҋ@��Ԃ̓G��������
		if (mpEnemy[i]->GetEnemyMainState() == EnemyMainState::CREATE_BEFORE)
		{
			//�o����Ԃ�
			mpEnemy[i]->GetStateCreateBefore()->ChangeState();
		}

		//�G�̍X�V����
		mpEnemy[i]->Update();
	}

	//�{�X�G�g�p���̏���
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

		//������ԂȂ�΁A��������
		if (mpBossEnemy->GetState() == BossEnemyMainState::CREATE&&
			this->ChackSubordinateEnemyUseNum() <= SUBORDINATE_ENEMY_ARIVE_NUM)
		{
			//��������
			this->CreateSubordinateEnemy();
		}

		//�z���G�̍X�V����
		for (int j = 0; j < SUBORDINATE_ENEMY_NUM; j++)
		{
			//���g�p���͏��������Ȃ�
			if (!mpSubordinateEnemy[j]->GetUseFlag())continue;

			//�����v���C���[���_���[�W��ԂɂȂ�����
			mpSubordinateEnemy[j]->Update();
		}
	}
}

/*=================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::Draw()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		//���g�p��Ԃ̓G�͒ʂ��Ȃ�
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//��O�����̏ꍇ��������ʂ��Ȃ�
		if (mpEnemy[i]->GetMovePhaseNumber() == Utility::EXCEPTION_NUM) continue;

		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() <= mNowPhaseNum)
		{
			mpEnemy[i]->Draw();
		}
	}
	if (mBossEnemyUseFlag)
	{
		//�{�X�G�̕`�揈��
		mpBossEnemy->Draw();

		//�z���G�̕`�揈��
		for (int j = 0; j < SUBORDINATE_ENEMY_NUM; j++)
		{
			//���g�p���͏��������Ȃ�
			if (!mpSubordinateEnemy[j]->GetUseFlag())continue;

			mpSubordinateEnemy[j]->Draw();
		}
	}
	
}

/*=================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		if (mpEnemy[i] != nullptr) 
		{
			mpEnemy[i]->Finalize();
		}	
	}
}

/*========================================
���Z�b�g����(�|�C���^�͕ێ�)
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void EnemyManager::Reset()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		if (mpEnemy[i] != nullptr)
		{
			mpEnemy[i]->SelfDestroy();
		}
	}
}

/*=================================
�ǂݍ��ރt�@�C�������쐬
�����F�X�e�[�W�ԍ�
�Ԃ�l�F�t�@�C����
===================================*/
std::string EnemyManager::CreateLoadEnemyFileName(const std::string & stagenum)
{
	std::string filetop = "Resources/CSV/Enemy",
		filebottom = ".csv",
		filename = "none";

	filename = filetop + stagenum + filebottom;

	return filename;

}


/*==========================================
�S�Ă̓G�����S�������Ƃ��m�F����t���O
�����F�Ȃ�
�Ԃ�l�F�����t���O
==========================================*/
bool EnemyManager::AllEnemyDeathFlag()
{
	//���݂̃t�F�[�Y���ő�t�F�[�Y�o�Ȃ��Ȃ�Ώ�����ʂ��Ȃ�
	if (mNowPhaseNum != mMaxPhaseNum)
	{
		return false;
	}

	//�G�̐������s��
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���Ă���G��������
		if (mpEnemy[i]->GetUseFlag())
		{
			//false��Ԃ�
			return false;
		}
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
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::ExplosionSimultaneousEnemy()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//���g�p��Ԃ̓G�͒ʂ��Ȃ�
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//�폜����
		mpEnemy[i]->SelfDestroy();

		//�G�t�F�N�g�̐ݒ�
		EnemyCommonFunction::SetEnemyEffect
		(
			eEffectType::BOMB,
			mpEnemy[i]->GetEnemyModel()->GetPosition()
		);
	}
	if (mBossEnemyUseFlag)
	{
		//�G�t�F�N�g�̐ݒ�
		EnemyCommonFunction::SetEnemyEffect
		(
			eEffectType::BOMB,
			mpBossEnemy->GetEnemyModel()->GetPosition()
		);

		//�폜����
		mpBossEnemy->SelfDestroy();

		//�z���G�̕`�揈��
		for (int j = 0; j < SUBORDINATE_ENEMY_NUM; j++)
		{
			//���g�p���͏��������Ȃ�
			if (!mpSubordinateEnemy[j]->GetUseFlag())continue;

			//�G�t�F�N�g�̐ݒ�
			EnemyCommonFunction::SetEnemyEffect
			(
				eEffectType::BOMB,
				mpSubordinateEnemy[j]->GetEnemyModel()->GetPosition()
			);

			//�폜����
			mpSubordinateEnemy[j]->SelfDestroy();
		}
	}
}

/*===================================
�u���b�N�Փ˃t���O������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::ResetEnemyBlockHitFlag()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!mpEnemy[i]->GetUseFlag()) continue;

		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum)continue;

		//�G�̌��݂̏�Ԃ��ړ���ԈȊO�Ȃ��
		if (mpEnemy[i]->GetEnemyMainState() != EnemyMainState::MOVE)continue;

		//�Փ˃t���O������
		if (mpEnemy[i]->GetStateMove()->GetBlockHitFlag() == EnemyMainStateMove::EnemyBlockHit::HIT)
		{
			mpEnemy[i]->GetStateMove()->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NOT_HIT);
		}	
	}
}

/*===================================
�z���G����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::CreateSubordinateEnemy()
{
	//�Z�k�p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 position = NOT_SET_ENEMY_POSITION;
	
	//������
	int createNum{ 0 };
	
	//�A�h���X�ۑ��p�ϐ�
	std::vector<SubordinateEnemy*> pAddress;
	
	//�z���G�̐�������
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM && createNum < SUBORDINATE_ENEMY_CREATE_NUM; i++)
	{
		//�g�p���̓G�͏������Ȃ�
		if (mpSubordinateEnemy[i]->GetUseFlag())continue;
		
		position = this->CreatePosition(mpBossEnemy->GetEnemyModel()->GetPosition());
		mpSubordinateEnemy[i]->Initialize(position);
		createNum++;
	
		//�A�h���X�ۑ�
		pAddress.push_back(mpSubordinateEnemy[i].get());
	}
	//�{�X�G�ɕۑ�����
	mpBossEnemy->SetSaveSubordinateEnemy(pAddress);
	
	createNum = 0;

	pAddress.clear();
	
	//�ʏ�G�̐�������
	for (int i = 0; i < static_cast<int>(mpEnemy.size()) && createNum < NORNAML_ENEMY_CREATE_NUM; i++)
	{
		//�g�p���̓G�͏������Ȃ�
		if (mpEnemy[i]->GetUseFlag())continue;
	
		position = this->CreatePosition(mpBossEnemy->GetEnemyModel()->GetPosition());
		mpEnemy[i]->Initialize(position);
		mpEnemy[i]->SetMovePhaseNumber(NORMAL_ENEMY_CREATE_PHASE);
		createNum++;
	}
}

/*===================================
�g�p���̃|�C���^�̃A�N�Z�T:private
�����F�t�@�C���p�X�A�J�����ւ̃A�h���X
�Ԃ�l�F�e�G�̉ϒ��z��
===================================*/
std::vector<Enemy*> EnemyManager::GetUseNormalEnemyVector()
{
	std::vector<Enemy*> returnVector{};
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!mpEnemy[i]->GetUseFlag()) continue;
		
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum)continue;

		returnVector.push_back(mpEnemy[i].get());
	}

	return returnVector;
}
BossEnemy* EnemyManager::GetBossEnemyVector()
{
	BossEnemy* returnEnemy{};
	if (mBossEnemyUseFlag)
	{
		returnEnemy = mpBossEnemy.get();
	}
	return returnEnemy;
}
std::vector<SubordinateEnemy*> EnemyManager::GetUseSubordinateEnemyVector()
{
	std::vector<SubordinateEnemy*> returnVector{};
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		//���g�p���͏��������Ȃ�
		if (!mpSubordinateEnemy[i]->GetUseFlag())continue;

		returnVector.push_back(mpSubordinateEnemy[i].get());
	}

	return returnVector;
}

/*===================================
�t�@�C����������擾����:private
�����F�t�@�C���p�X�A�J�����ւ̃A�h���X
�Ԃ�l�F�Ȃ�
===================================*/
void EnemyManager::LoadFile(std::string filepath)
{
	//������
	DirectX::SimpleMath::Vector3 position = NOT_SET_ENEMY_POSITION;
	int phasenum = 0;


	//���ǂݍ���
	mpEnemyCall->LoadInfo(filepath);

	//BOSS��������
	mBossEnemyUseFlag = this->CreateBoss();

	
	//�T�C�Y�����߂Ďw��
	//BOSS�����݂���ꍇ�͗]���Ƀ��������m�ۂ���
	if (mBossEnemyUseFlag)
	{
		mpEnemy.resize(mpEnemyCall->GetNormalEnemyStructerSize()+ ENEMY_ADDITIONAL_CAPACITY);
	}
	else
	{
		mpEnemy.resize(mpEnemyCall->GetNormalEnemyStructerSize());
	}	

	//����
	int i = 0;
	for (i; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//��񂪍ő�T�C�Y�ɂȂ�����(����ȏ�G��񂪂Ȃ����)
		if (i == mpEnemyCall->GetNormalEnemyStructerSize()) 
		{
			//for���𔲂���B
			break;
		}
		position = mpEnemyCall.get()->GetNormalEnemyStructer(i).mVectorESPosition;
		phasenum = mpEnemyCall.get()->GetNormalEnemyStructer(i).mPhaseNumber;
		mpEnemy[i]->SetMovePhaseNumber(phasenum);
		mpEnemy[i]->Initialize(position);
	}



	//�s�v�ɂȂ����̂ō폜
	mpEnemyCall->Reset();
}

/*======================================================================
�{�X�G��������
�����F�Ȃ�
�Ԃ�l�F�����t���O
========================================================================*/
bool EnemyManager::CreateBoss()
{
	if (mpEnemyCall->GetBossEnemyStructer().mPhaseNumber == 0)return false;

	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 position = NOT_SET_ENEMY_POSITION;
	int phasenum = 0;

	//BOSS����
	position = mpEnemyCall->GetBossEnemyStructer().mVectorESPosition;
	phasenum = mpEnemyCall->GetBossEnemyStructer().mPhaseNumber;
	mpBossEnemy->SetMovePhaseNumber(phasenum);
	mpBossEnemy->Initialize(position);

	return true;
}



/*==================================================
���W����:private
�����F��ƂȂ���W
�Ԃ�l�F�������W
===================================================*/
DirectX::SimpleMath::Vector3 EnemyManager::CreatePosition(const DirectX::SimpleMath::Vector3& position)
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
	castPosition.x = static_cast<float>(randX(mt));
	castPosition.z = static_cast<float>(randZ(mt));

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


/*==================================================
�z���G�̐������`�F�b�N:private
�����F�Ȃ�
�Ԃ�l�F������
===================================================*/
int EnemyManager::ChackSubordinateEnemyUseNum()
{
	int returnNum{ 0 };
	for (int i = 0; i < SUBORDINATE_ENEMY_NUM; i++)
	{
		//���g�p���͏��������Ȃ�
		if (!mpSubordinateEnemy[i]->GetUseFlag())continue;

		returnNum++;
	}

	return returnNum;
}
