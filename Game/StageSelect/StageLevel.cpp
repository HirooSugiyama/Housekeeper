/*
�X�e�[�W�̃��x���`��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include"pch.h"
#include"StageLevel.h"



//�摜�������W
const DirectX::SimpleMath::Vector2 StageLevel::STAGELEVELOCITY_TEXTURE_INIT_POSITION(855.f, 615.f);

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 StageLevel::STAGELEVELOCITY_TEXTURE_SCALE(1.2f,1.2f);

//�摜�����炷��
const float StageLevel::STAGELEVELOCITY_SHIFT_POSITION_X = 50.f;


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
StageLevel::StageLevel()
	:mpStarTexture()
{
	for (int i = 0; i < STAGE_MAX_LEVELOCITY; i++)
	{
		mpStarTexture[i] = std::make_unique<ObjectTexture>();
	}
}

/*===================================
�f�X�g���N�^
===================================*/
StageLevel::~StageLevel()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void StageLevel::Initialize()
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAR));

	for (int i = 0; i < STAGE_MAX_LEVELOCITY; i++)
	{
		//�摜�ݒ�
		mpStarTexture[i]->SetTexture(textute);

		//����������
		mpStarTexture[i]->Initialize();

		//���W�ݒ�
		DirectX::SimpleMath::Vector2 position =
			STAGELEVELOCITY_TEXTURE_INIT_POSITION +
			DirectX::SimpleMath::Vector2(i * STAGELEVELOCITY_SHIFT_POSITION_X, 0.f);

		mpStarTexture[i]->SetPosition(position);

		//�g�嗦�ݒ�
		mpStarTexture[i]->SetScale(STAGELEVELOCITY_TEXTURE_SCALE);
	}
}

/*===================================
�`�揈��
�����F�X�e�[�W���x��
�Ԃ�l�F�Ȃ�
===================================*/
void StageLevel::Draw(const int& stagelevel)
{
	for (int i = 0; i<stagelevel; i++)
	{
		mpStarTexture[i]->Draw();
	}
}
