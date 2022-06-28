/*
�X�e�[�W���x���̊Ŕ�
�쐬�ҁF���R
�쐬���F2022/03/12
*/
#include"pch.h"
#include"StageLevelSignBoard.h"


//�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 StageLevelSignBoard::TEXTURE_SCALE(1.f,0.80f);
//�摜�̍��W
const DirectX::SimpleMath::Vector2 StageLevelSignBoard::TEXTURE_POSITON(640.f,435.f);

/*===================================
�R���X�g���N�^
===================================*/
StageLevelSignBoard::StageLevelSignBoard()
	:mpSignBoard()
{
	mpSignBoard = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
StageLevelSignBoard::~StageLevelSignBoard()
{
}

/*===================================
����������
===================================*/
void StageLevelSignBoard::Initialize()
{
	//�����ݒ�
	mpSignBoard->Initialize();
	//�摜�̐ݒ�
	const auto pResouceManager = ResourceManager::GetInstance();
	const auto texture = pResouceManager->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__SIGNBOARD));
	mpSignBoard->SetTexture(texture);

	//���W�ݒ�
	mpSignBoard->SetPosition(TEXTURE_POSITON);
	//�g�嗦�ݒ�
	mpSignBoard->SetScale(TEXTURE_SCALE);
}

/*===================================
�`�揈��
===================================*/
void StageLevelSignBoard::Draw()
{
	mpSignBoard->Draw();
}