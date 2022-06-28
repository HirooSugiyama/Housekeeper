/*
�x�����N���X
�쐬�ҁF���R
�쐬���F2021/10/06
*/
#include"pch.h"

#include"DangerousLine.h"

//�萔
//���W
const DirectX::SimpleMath::Vector3 DangerousLine::ASSETLINE_MODEL_POSITION(0.f, 0.75f, -5.f);
//�g�嗦							
const DirectX::SimpleMath::Vector3 DangerousLine::ASSETLINE_MODEL_SCALE(20.f, 3.f, 0.05f);

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
DangerousLine::DangerousLine()
	:
	mpAssertLineModel()
{
	mpAssertLineModel = std::make_unique<ObjectModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
DangerousLine::~DangerousLine()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void DangerousLine::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__ASSERTLINEMODEL));
	mpAssertLineModel->SetModel(model);
	mpAssertLineModel->SetPosition(ASSETLINE_MODEL_POSITION);
	mpAssertLineModel->SetScale(ASSETLINE_MODEL_SCALE);
}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void DangerousLine::Draw()
{
	//���f���`�揈��
	mpAssertLineModel->Draw();
}

/*============================================================
Z���W�̎擾(�G�t�F�N�g��������W)(�֐��̓s����CPP�ŏ���)
�����F�Ȃ�
�Ԃ�l�F���f����Z���W
============================================================*/
float DangerousLine::GetLinePositionZ()const
{
	float returnpos = mpAssertLineModel->GetPosition().z;

	return returnpos;
}




