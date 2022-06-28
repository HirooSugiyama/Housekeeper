/*
���탂�f������]�����邾���̃N���X
�쐬�ҁF���R
�쐬���F2021/10/15
*/
#include"pch.h"

#include"RotWeaponSample.h"

//���W
const DirectX::SimpleMath::Vector3 RotWeaponSample::ROTMODEL_POSITION(3.5f,1.f,0.f);
//�g�嗦
const DirectX::SimpleMath::Vector3 RotWeaponSample::ROTMODEL_SCALE(1.5f, 1.5f, 1.5f);
//��]���x
const float RotWeaponSample::ROT_SPEED = 0.5f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
RotWeaponSample::RotWeaponSample()
	:
	mpRotModel(nullptr),
	mModelRot(0.f)
{
	mpRotModel = std::make_unique<ObjectModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
RotWeaponSample::~RotWeaponSample()
{
}

/*=================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void RotWeaponSample::Initialize()
{
	//�g�嗦�ƍ��W�����炩���ߐݒ肵�Ă���
	mpRotModel->SetPosition(ROTMODEL_POSITION);
	mpRotModel->SetScale(ROTMODEL_SCALE);
}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void RotWeaponSample::Update()
{
	//���f������]������
	float rot = mpRotModel->GetRotAngleY() + ROT_SPEED;
	mpRotModel->SetRotationY(rot);
}

/*=================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void RotWeaponSample::Draw()
{
	//�������f����񂪓����Ă�����
	if (mpRotModel->GetModel() != nullptr)
	{
		//���f����`�悷��
		mpRotModel->Draw();
	}
}

/*==================================
���Z�b�g����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void RotWeaponSample::Reset()
{
	mModelRot = 0.f;
}

/*===================================
���f�������擾����
�����F���f�����
�Ԃ�l�F�Ȃ�
===================================*/
void RotWeaponSample::SetWeaponModel(DirectX::Model* model)
{
	mpRotModel->SetModel(model);
}




