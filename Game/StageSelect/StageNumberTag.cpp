/*
�X�e�[�W�I���^�O
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include"pch.h"
#include"StageNumberTag.h"

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 StageNumberTag::TEX_SCALE(0.85f,1.1f);

//�摜�`��ʒu���琔���`��ʒu���Z�o���邽�߂̒萔
const DirectX::SimpleMath::Vector2 StageNumberTag::NUM_SHIFT(225.f,-5.f);

/*=================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
StageNumberTag::StageNumberTag()
	:
	mpBackGround(nullptr),
	mDrawStageString(),
	mDrawPosition()
{
	mpBackGround = std::make_unique<ObjectTexture>();
	mpStageSpriteNum = std::make_unique<SpriteNumber2D>();
}

/*===================================
�f�X�g���N�^
===================================*/
StageNumberTag::~StageNumberTag()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void StageNumberTag::Initialize()
{
	//����������
	mpBackGround->Initialize();

	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGESCALE));

	//�摜�̐ݒ�
	mpBackGround->SetTexture(texture);
	//�g�嗦�̐ݒ�
	mpBackGround->SetScale(TEX_SCALE);



	//�X�R�A�̃t�H���g���w��
	mpStageSpriteNum->SetTextureKey(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGENUMBERFONT));
	mpStageSpriteNum->Initialize();
	mpStageSpriteNum->SetAlign(eAlign::LEFT);
	mpStageSpriteNum->SetScale(Utility::STRING_SIZE_SMALL);

}

/*===================================
�`�揈��
�����F�`��t���O(false �`�悵�Ȃ�)
�Ԃ�l�F�Ȃ�
===================================*/
void StageNumberTag::Draw(const bool& flag)
{
	//��O�����Ȃ珈�����s��Ȃ�
	if (mDrawStageString == Utility::EXCEPTION_NUM)
	{
		return;
	}
	if (!flag)
	{
		return;
	}

	//�w�i�̕`��
	mpBackGround->Draw();

	//�����̕`��
	mpStageSpriteNum->Create(mDrawStageString, mDrawPosition + NUM_SHIFT);
	mpStageSpriteNum->Draw();
}

/*===================================
�`��ʒu�̎w��
�����F���W
�Ԃ�l�F�Ȃ�
===================================*/
void StageNumberTag::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	mDrawPosition = position;
	mpBackGround->SetPosition(position);
}




