/*
�G�N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include<pch.h>
#include "Enemy.h"

//�O���錾
#include"../../../Common/ObjectTexture.h"

//�֐��̎g�p
#include"../Block/Block.h"

//�֐��̎g�p
#include"EnemyCommonFunction.h"


//�萔

//�ړ����x
const float Enemy::ENEMY_MOVE_SPEED = 0.01f;


//���f���`��͈͎w��
const float Enemy::ENEMY_MDEL_DROW_AREA = -70.f;

//�u���b�N�ԍ���O����
const int Enemy::ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM = -1;

//�G���f���������I�ɉ��Ɍ�����(�������]����ۂɎg�p)
const float Enemy::ENEMY_MODEL_FORCED_BESIDE = 270.f;

//�G��HP
const int Enemy::ENEMY_HP = 20;

//���]��
const int Enemy::REVERSE_NUM = 2;

//�U����
const int Enemy::ENEMY_ATTACK_NUM = 1;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Enemy::Enemy()
	: 
	IEnemy(),
	mMovePhaseNumber(),

	mpMainState(nullptr),
	mpCreateBefore(nullptr),
	mpMove(nullptr),
	mpDamage(nullptr),
	mpDisappearance(nullptr),
	mState(EnemyMainState::CREATE_BEFORE),
	mEnemyModelAngle(eAngleEnemy::STRAIGHT)
	
{
	//���f����ݒ肷��
	this->SetEnemyModel();

	mpCreateBefore = std::make_unique<EnemyMainStateCreateBefore>();
	mpMove = std::make_unique<EnemyMainStateMove>();
	mpDamage = std::make_unique<EnemyMainStateDamage>();
	mpDisappearance = std::make_unique<EnemyMainStateDisappearance>();

}

/*===================================
�f�X�g���N�^
===================================*/
Enemy::~Enemy()
{
}

/*=================================
������
�����F�������W
�Ԃ�l�F�Ȃ�
===================================*/
void Enemy::Initialize(const DirectX::SimpleMath::Vector3& position)
{
	//���g�p��ԂƂ���
	IEnemy::GetEnemyModel()->SetModelUseFlag(true);

	//�e����W��ݒ�
	IEnemy::GetEnemyModel()->SetPosition(position);
	IEnemy::GetEnemyModel()->SetScale(IEnemy::GetEnemyScale());
	IEnemy::GetEnemyModel()->SetRotationY(IEnemy::GetEnemyModelMissFixRotation());	//���f���������~�X�̏C��

	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = IEnemy::GetEnemyModel()->ReturnHalfSize(IEnemy::GetEnemyScale());
	//���f���̌`�ɍ��킹�ăT�C�Y����
	halfsize.y *= IEnemy::GetEnemyColliderExtendY();
	halfsize.z *= IEnemy::GetEnemyColliderExtendZ();

	//�ݒ�
	IEnemy::GetEnemyModel()->SetAABBCollider(position - halfsize, position + halfsize);

	//�e�̏���������
	IEnemy::GetShadow()->WrapInitialize();
	//�e�̊g�嗦�����߂�
	IEnemy::GetShadow()->SetScale
	(
		DirectX::SimpleMath::Vector2
		(
			IEnemy::GetEnemyScale().x,
			IEnemy::GetEnemyScale().z
		)
	);	//XZ����

	//���ꂼ��̏�Ԃ̏�����
	mpCreateBefore->Initialize(this);
	mpMove->Initialize(this);
	mpDamage->Initialize(this);
	mpDisappearance->Initialize(this);


	//�ŏ��̏�Ԃ͑ҋ@����
	this->ChangeStateCreateBefore();

}

/*===================================
�X�V
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Enemy::Update()
{
	//�g�p���̎��̂ݒʂ�
	if (IEnemy::GetEnemyModel()->GetModelUseFlag())
	{
		//State�ŊǗ����ꂽ�ړ��������s��
		mpMainState->Update();

		/*�����蔻��̍X�V*/
		//�����ł͕ۑ����ĂȂ����߃��f������Ăяo���B
		DirectX::SimpleMath::Vector3 modelPosition, modelscale;
		modelPosition = IEnemy::GetEnemyModel()->GetPosition();
		modelscale = IEnemy::GetEnemyModel()->GetScale();
		//�g�嗦�̔����̒l�𐶐�
		DirectX::SimpleMath::Vector3 halfsize = IEnemy::GetEnemyModel()->ReturnHalfSize(modelscale);
		//���f���̌`�ɍ��킹�ăT�C�Y����
		halfsize.y *= IEnemy::GetEnemyColliderExtendY();
		halfsize.z *= IEnemy::GetEnemyColliderExtendZ();
		//�ݒ�
		IEnemy::GetEnemyModel()->SetAABBCollider(modelPosition - halfsize, modelPosition + halfsize);
	}

	//�_���[�W���l�G�t�F�N�g�̍X�V����
	IEnemy::GetFloatNumber3D()->Update();
}

/*===================================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Enemy::Draw()
{
	//���g�p���͏��������Ȃ�
	if (!IEnemy::GetEnemyModel()->GetModelUseFlag())return;


	//���f�����w��͈͂ɓ����Ă�����`�悷��
	if (IEnemy::GetEnemyModel()->GetPosition().z >= ENEMY_MDEL_DROW_AREA)
	{
		//�e�̕`��
		IEnemy::GetShadow()->Draw(IEnemy::GetEnemyModel()->GetPosition());

		//State��̕`��
		mpMainState->Draw();
	}

	//�_���[�W���l�G�t�F�N�g�̕`�揈��
	IEnemy::GetFloatNumber3D()->Draw();
}


/*=================================================
�u���b�N�U������:private
�����F�u���b�N�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================================*/
void Enemy::AttackBlock(Block* pBlock)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�Փ˔���
	bool flag = false;
	flag = pC.Intersect
	(
		mpMove->GetAABBCollider(),
		pBlock->GetBoxModel()->GetAABBCollider()
	);

	//�������Ă��Ȃ��ꍇ�̏���
	if (!flag)
	{
		//���߂ē��������Ǐ����폜����
		mpMove->SetFirstHitBlock(nullptr);
		//�Փ˃t���O��������
		mpMove->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NONE);
		//�������Ă��Ȃ��ǂ͍U���ł��Ȃ����߁A�ړ������Ƃ���
		mpMove->ChangeStateWalk();
		return;
	}

	//�U������^�C�~���O�ł͂Ȃ�������
	if (!mpMove->AttackFlag())return;

	//�u���b�N�Ƀ_���[�W��^����
	bool blockHP = pBlock->BlockDamage(ENEMY_ATTACK_NUM);

	//�G�t�F�N�g��ݒ肷��
	EnemyCommonFunction::SetEnemyEffect(eEffectType::CLAW, pBlock->GetBoxModel()->GetPosition());

	//�����u���b�N��HP���Ȃ�������
	if (blockHP)
	{
		//�u���b�N��j�󂷂�
		pBlock->SelfDestroy();

		//���߂ē��������Ǐ����폜����
		mpMove->SetFirstHitBlock(nullptr);

		//�Փ˃t���O��������
		mpMove->SetBlockHitFlag(EnemyMainStateMove::EnemyBlockHit::NONE);

		//�G�t�F�N�g�̐ݒ�
		EnemyCommonFunction::SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
	}
}

/*==================================================
�u���b�N�������:private
�����F�u���b�N�̃|�C���^
�Ԃ�l�F�Ȃ�
===================================================*/
void Enemy::AvoidanceBlock(Block* pBlock)
{
	//�u���b�N�ԍ����擾
	Block* block = mpMove->GetFirstHitBlock();

	//2�x���]���Ă���A�Ώۂ̃u���b�N���ŏ��ɐG�ꂽ�u���b�N�Ȃ��
	if (block == pBlock && mpMove->GetReverseNum() >= REVERSE_NUM)
	{
		//�U����ԂƂ���
		mpMove->ChangeStateWallAttack();

		//�u���b�N�̎g�p����ۑ�����
		mpMove->SetAttackBlock(pBlock->GetBlockUseFlagAddress());
	}

	//���̑��̓��e�������Ă����珈�������Ȃ�
	else if (block != nullptr)return;

	//�����G�����s���Ă�����
	if (mpMove->GetMoveState() == EnemyMoveState::WALK)
	{
		//��]�ɐ؂�ւ���
		mpMove->ChangeStateRotation();

		//�ǂ̃A�h���X��ۑ�����
		mpMove->SetFirstHitBlock(pBlock);
	}
}



/*===================================
�ړ�����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Enemy::Move()
{
	DirectX::SimpleMath::Vector3 vel;
	vel.z = ENEMY_MOVE_SPEED;

	IEnemy::GetEnemyModel()->Move(vel);
}


/*===================================
���f����ݒ肷��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Enemy::SetEnemyModel()
{
	//���\�[�X�}�l�[�W���̏���
	//�����ɍ��킹�����f����ݒ肷��
	auto pRM = ResourceManager::GetInstance();

	//�G��ɍ��킹�����f����ݒ肷��
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__ZONBI));

	//�ݒ肷��
	IEnemy::GetEnemyModel()->SetModel(model);
}


