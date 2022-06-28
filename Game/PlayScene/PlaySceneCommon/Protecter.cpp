/*
���_�N���X
�쐬�ҁF���R
�쐬���F2021/05/21
*/

#include<pch.h>
#include"Protecter.h"

//���f���̍��W
const float Protecter::PROTECTER_MODEL_POSITION_X = -0.51f;
const float Protecter::PROTECTER_MODEL_POSITION_Y = 0.7f;
const float Protecter::PROTECTER_MODEL_POSITION_Z = 16.f;
//���f���̊g�嗦
	//�����ڗp
const float Protecter::PROTECTER_MODEL_SCALE_X = 30.0f;
const float Protecter::PROTECTER_MODEL_SCALE_Y = 10.5f;
const float Protecter::PROTECTER_MODEL_SCALE_Z = 5.5f;

//���f�������~�X�̊p�x����
const float Protecter::PROTECTER_DEBUG_SHIFT_ANGLE = 180.f;


/*==============
�R���X�g���N�^
�����F�Ȃ�
==============*/
Protecter::Protecter()
	:
	mpProtecterModel(nullptr),
	mDamageFlag(false)
{

	mpProtecterModel = std::make_unique<BoxModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
Protecter::~Protecter()
{
}

/*==============
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============*/
void Protecter::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__NEWHOUSESET));
	mpProtecterModel->SetModel(model);


	DirectX::SimpleMath::Vector3 position, scale;
	position.x = PROTECTER_MODEL_POSITION_X;
	position.y = PROTECTER_MODEL_POSITION_Y;
	position.z = PROTECTER_MODEL_POSITION_Z;

	mpProtecterModel->SetPosition(position);
	mpProtecterModel->SetScale(scale);
	mpProtecterModel->SetScale(DirectX::SimpleMath::Vector3::One);
	mpProtecterModel->SetRotationY(PROTECTER_DEBUG_SHIFT_ANGLE);

	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpProtecterModel->ReturnHalfSize
	(
		DirectX::SimpleMath::Vector3
		(
			PROTECTER_MODEL_SCALE_X,
			PROTECTER_MODEL_SCALE_Y,
			PROTECTER_MODEL_SCALE_Z
		)
	);
	//�ݒ�
	mpProtecterModel->SetAABBCollider(position - halfsize, position + halfsize);
}

/*==============
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============*/
void Protecter::Draw()
{
	mpProtecterModel->Draw();
}

/*==========================
�ڂ뉮�ɐ؂�ւ�
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==========================*/
void Protecter::ChangeOldHouse()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__OLDHOUSESET));
	mpProtecterModel->SetModel(model);
}

