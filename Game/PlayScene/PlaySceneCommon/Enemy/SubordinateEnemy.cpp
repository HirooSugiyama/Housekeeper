/*
�z���G�N���X
�쐬�ҁF���R
�쐬���F2022/02/11
*/
#include"pch.h"

#include"SubordinateEnemy.h"

//�O���錾
#include"State/EnemyMainStateBase.h"


//�z���G��HP
const int SubordinateEnemy::SUBORDINATE_ENEMY_HP = 5;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
SubordinateEnemy::SubordinateEnemy()
	:
	IEnemy(),
	mpState(),
	mState(),
	mpCrateBefore(),
	mpMove(),
	mpDisappearance()
{
	mpCrateBefore = std::make_unique<EnemyMainStateCreateBefore>();
	mpMove = std::make_unique<SubordinateEnemyMainStateMove>();
	mpDisappearance = std::make_unique<EnemyMainStateDisappearance>();

	//�g�p�t���O�����낵�Ă���
	IEnemy::GetEnemyModel()->SetModelUseFlag(false);

	//���\�[�X�}�l�[�W���̏���
	//�����ɍ��킹�����f����ݒ肷��
	auto pRM = ResourceManager::GetInstance();

	//�G��ɍ��킹�����f����ݒ肷��
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__ZONBI));

	//�ݒ肷��
	IEnemy::GetEnemyModel()->SetModel(model);

	//�e�̏���������
	IEnemy::GetShadow()->WrapInitialize();
}

/*===================================
�f�X�g���N�^
===================================*/
SubordinateEnemy::~SubordinateEnemy()
{
}

/*===================================
����������
�����F�������W
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemy::Initialize(const DirectX::SimpleMath::Vector3& position)
{
	//�g�p��ԂƂ���
	IEnemy::GetEnemyModel()->SetModelUseFlag(true);
	
	
	//�e����W��ݒ�
	IEnemy::GetEnemyModel()->SetPosition(position);
	IEnemy::GetEnemyModel()->SetScale(IEnemy::GetEnemyScale());
	
	//���f���������~�X�̏C��
	IEnemy::GetEnemyModel()->SetRotationY(IEnemy::GetEnemyModelMissFixRotation());
	
	//�e�̊g�嗦�����߂�
	IEnemy::GetShadow()->SetScale
	(
		DirectX::SimpleMath::Vector2
		(
			IEnemy::GetEnemyScale().x,
			IEnemy::GetEnemyScale().z
		)
	);	//XZ����
	
	
	//�e��Ԃ̏���������
	mpCrateBefore->Initialize(this);
	mpMove->Initialize(this);
	mpDisappearance->Initialize(this);
	
	//������Ԃ�ݒ�
	this->ChangeStateCreateBefore();
	this->GetStateCrateBefore()->ChangeState();	

	//�ړ��ʂ̏�����
	IEnemy::GetEnemyModel()->Move(DirectX::SimpleMath::Vector3::Zero);
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemy::Update()
{

	//���݂̏�Ԃ̍X�V����
	mpState->Update();
	
	//�����蔻��ݒ菈��
	this->SetCollider();
}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemy::Draw()
{
	//���݂̏�Ԃ̍X�V����
	mpState->Draw();

	//�e�̏���������
	IEnemy::GetShadow()->Draw(IEnemy::GetEnemyModel()->GetPosition());
}

/*==================================
�����蔻��ݒ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void SubordinateEnemy::SetCollider()
{
	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = IEnemy::GetEnemyModel()->ReturnHalfSize(IEnemy::GetEnemyScale());
	//���W���擾
	DirectX::SimpleMath::Vector3 position = IEnemy::GetEnemyModel()->GetPosition();

	//���f���̌`�ɍ��킹�ăT�C�Y����
	halfsize.y *= IEnemy::GetEnemyColliderExtendY();
	halfsize.z *= IEnemy::GetEnemyColliderExtendZ();

	//�ݒ�
	IEnemy::GetEnemyModel()->SetAABBCollider(position - halfsize, position + halfsize);
}

