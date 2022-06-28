/*
�{�X�G�N���X
�쐬�ҁF���R
�쐬���F2022/02/11
*/
#include"pch.h"

#include"BossEnemy.h"

//�O���錾
#include"State/EnemyMainStateBase.h"

//�֐��̎g�p
#include"SubordinateEnemy.h"

//�F���͈͂̊g�嗦
const float BossEnemy::RECOGITION_RANGE_SCALE = 3.f;

//�{�X�G��HP
const int BossEnemy::BOSS_ENEMY_HP = 40;


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
BossEnemy::BossEnemy()
	:
	IEnemy(),
	mpPlayerRecognitionRange(),
	mpSaveSubordinateEnemy{},
	mPlayerRecognitionRangeCollider(),
	mActiveFlag(),
	mpMainState(),
	mState(),
	mpCreateBefore(),
	mpDisappearance(),
	mpMove(),
	mpAttack(),
	mpCreate()
{
	mpPlayerRecognitionRange = std::make_unique<FlatPolygon>();
	mpCreateBefore = std::make_unique<EnemyMainStateCreateBefore>();
	mpDisappearance = std::make_unique<EnemyMainStateDisappearance>();
	mpMove = std::make_unique<BossEnemyMainStateMove>();
	mpAttack = std::make_unique<BossEnemyMainStateAttack>();
	mpCreate = std::make_unique<BossEnemyMainStateCreate>();
}

/*===================================
�f�X�g���N�^
===================================*/
BossEnemy::~BossEnemy()
{
}

/*===================================
����������
�����F�������W
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemy::Initialize(const DirectX::SimpleMath::Vector3& position)
{
	//�g�p�t���O�����Ă�
	IEnemy::GetEnemyModel()->SetModelUseFlag(true);

	//���\�[�X�}�l�[�W���̏���
	//�����ɍ��킹�����f����ݒ肷��
	auto pRM = ResourceManager::GetInstance();

	//�G��ɍ��킹�����f����ݒ肷��
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__BOSSENEMY));

	//�ݒ肷��
	IEnemy::GetEnemyModel()->SetModel(model);

	//�e����W��ݒ�
	IEnemy::GetEnemyModel()->SetPosition(position);
	IEnemy::GetEnemyModel()->SetScale(IEnemy::GetEnemyScale());
	IEnemy::GetEnemyModel()->SetRotationY(IEnemy::GetEnemyModelMissFixRotation());	//���f���������~�X�̏C��

	//�����蔻��ݒ�
	this->SetCollider();

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


	//�e��Ԃ̏���������
	mpCreateBefore->Initialize(this);
	mpDisappearance->Initialize(this);
	mpMove->Initialize(this);
	mpAttack->Initialize(this);
	mpCreate->Initialize(this);

	//�ŏ��͐����O���
	this->ChangeStateCreateBefore();

	//�F���͈͂̏���������
	mpPlayerRecognitionRange->Initialize();
	mpPlayerRecognitionRange->SetScale
	(
		DirectX::SimpleMath::Vector2(RECOGITION_RANGE_SCALE, RECOGITION_RANGE_SCALE)
	);
	mpPlayerRecognitionRange->SetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__CIRCLE));
}

/*==================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemy::Update()
{
	//���݂̏�Ԃ̍X�V����
	mpMainState->Update();

	//�����蔻��ݒ�
	this->SetCollider();

	//�A�h���X�폜����
	this->DeleteSubordinateEnemyAddress();

	//�_���[�W���l�G�t�F�N�g�̍X�V����
	IEnemy::GetFloatNumber3D()->Update();

}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemy::Draw()
{
	//�F���͈͂̕`�揈��
	mpPlayerRecognitionRange->Draw(IEnemy::GetEnemyModel()->GetPosition());

	//���݂̏�Ԃ̕`�揈��
	mpMainState->Draw();

	//�_���[�W���l�G�t�F�N�g�̕`�揈��
	IEnemy::GetFloatNumber3D()->Draw();
}

/*==================================
�z���G�̃A�h���X�Ǘ��p�ϐ��̃A�N�Z�T
�����F�z���G�̉ϒ��z��
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemy::SetSaveSubordinateEnemy(std::vector<SubordinateEnemy*> pSubordinateEnemy)
{
	//�T�C�Y��0�Ȃ璼�ڑ}��
	int arraySize = mpSaveSubordinateEnemy.size();

	if (arraySize == 0)
	{
		mpSaveSubordinateEnemy = pSubordinateEnemy;
	}
	else
	{
		//�T�C�Y�g��
		mpSaveSubordinateEnemy.resize(arraySize + pSubordinateEnemy.size());
		arraySize = mpSaveSubordinateEnemy.size();
		
		//�}��
		int argumentArray = 0;
		int i = 0;
		for (i; i < arraySize && argumentArray< static_cast<int>(pSubordinateEnemy.size()); i++)
		{
			//�g�p���̂Ƃ���ɂ͓���Ȃ�
			if (mpSaveSubordinateEnemy[i]!=nullptr&&mpSaveSubordinateEnemy[i]->GetUseFlag())continue;
			mpSaveSubordinateEnemy[i] = pSubordinateEnemy[argumentArray];
			argumentArray++;
		}
		
		//�T�C�Y�Đݒ�
		mpSaveSubordinateEnemy.resize(i);
	}
}

/*==================================
�����蔻��ݒ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemy::SetCollider()
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

	//�F���͈͂̍X�V
	mPlayerRecognitionRangeCollider.mCenter = position;
	mPlayerRecognitionRangeCollider.mRadius = RECOGITION_RANGE_SCALE;
}

/*==================================
�|�C���^�폜����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void BossEnemy::DeleteSubordinateEnemyAddress()
{
	//�T�C�Y��0�Ȃ璼�ڑ}��
	int arraySize = mpSaveSubordinateEnemy.size();

	for (int i = 0; i < arraySize ; i++)
	{
		if (mpSaveSubordinateEnemy[i] == nullptr)continue;

		//���g�p�̗v�f����������null�ŏ���������
		if (!mpSaveSubordinateEnemy[i]->GetUseFlag())
		{
			mpSaveSubordinateEnemy[i] = nullptr;
		}
	}
}
