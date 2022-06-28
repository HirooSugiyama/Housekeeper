/*
��Q���N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/


#include<pch.h>
#include "Block.h"


//�萔
//��ޕʃu���b�N�̑ϋv�x
//Wood
const int Block::BLOCK_DURABILITY = 10;


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Block::Block()
	:
	mpBlockModel(nullptr),
	mBlockUseFlag(false),
	mBlockHP(0),
	mIsGravity(false),
	mpArchitecture(nullptr),
	mpNormal(nullptr),
	mpBlockKindBase(nullptr)
{
	mpBlockModel = std::make_unique<BoxModel>();
	mpNormal = std::make_unique<BKStateNormal>();
	mpArchitecture = std::make_unique<BKStateArchitecture>();
}

/*===================================
�f�X�g���N�^
===================================*/
Block::~Block()
{
}

/*=================================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Block::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__WOODBLOCK));
	mpBlockModel->SetModel(model);

	//State�̏�����
	mpNormal->Initialize(this);
	mpArchitecture->Initialize(this);
}


/*===================================
�X�V
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Block::Update()
{
	//���f���`�撆�łȂ��Ȃ�
	if (mpBlockModel->GetDrawFlag()==false)
	{
		//���g�p��Ԃɂ���
		mBlockUseFlag = false;
	}

	bool createjuge=mpBlockKindBase->Update();
	//�������z�������I�������
	if (createjuge) 
	{
		this->ChangeStateNormal();
	}	

}

/*=============================================
��������
�����F	position(���W)�Ascale(�g�又��)
�Ԃ�l�F�Ȃ�
===============================================*/
void Block::Create(const DirectX::SimpleMath::Vector3& position,
					const DirectX::SimpleMath::Vector3& scale)
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();

	//�u���b�N���g�p���ɂ���
	mBlockUseFlag = true;
	//�g�p���̂��߃u���b�N��\��
	mpBlockModel->SetDrawFlag(true);

	//���f�����擾����
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__WOODBLOCK));

	//���f�����Đݒ肷��
	mpBlockModel->SetModel(model);

	//���ނ����Ƃ�HP��ݒ肷��
	mBlockHP = BLOCK_DURABILITY;

	//�u���b�N�̏����ݒ�
	mpBlockModel->SetPosition(position);
	mpBlockModel->SetScale(scale);

	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpBlockModel->ReturnHalfSize(scale);
	//�ݒ�
	mpBlockModel->SetAABBCollider(position - halfsize, position + halfsize);

	//�Ƃ肠�������z������
	this->ChangeStateArchitecture();
	//���Z�b�g����
	mpBlockKindBase->Reset();

}

/*===================================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Block::Draw()
{
	if (mBlockUseFlag)
	{
		mpBlockModel->Draw();
	}
}


/*===================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Block::Finalize()
{
	mpBlockModel.reset();
}

/*===================================
���g���폜(�|�C���^�Ȃǂ͏��ł��Ȃ�)
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Block::SelfDestroy()
{
	if (mpBlockModel->GetDrawFlag())
	{
		mpBlockModel->SetDrawFlag(false);

		DirectX::SimpleMath::Vector3 position =mpBlockModel->GetPosition();
		DirectX::SimpleMath::Vector3 scale=mpBlockModel->GetScale();


		//�����蔻��������l�ɖ߂�
		DirectX::SimpleMath::Vector3 resetPosition(DirectX::SimpleMath::Vector3::Zero);
		mpBlockModel->SetAABBCollider(resetPosition, resetPosition);

		//�u���b�N�𖢎g�p��Ԃɂ���
		mBlockUseFlag = false;
	}
}