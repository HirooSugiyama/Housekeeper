/*
���������摜�N���X
�쐬�ҁF���R
�쐬���F2021/12/17
*/
#include"pch.h"

#include"MoveSpriteNumber2D.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
MoveSpriteNumber2D::MoveSpriteNumber2D()
	:
	mpCountNumber(),
	mpSpriteNumber2D(),
	mDrawPosition()
{
	mpCountNumber = std::make_unique<CountNumber>();
	mpSpriteNumber2D = std::make_unique<SpriteNumber2D>();
}

/*===================================
�f�X�g���N�^
===================================*/
MoveSpriteNumber2D::~MoveSpriteNumber2D()
{
}

/*===================================
����������
�����F	�摜�p�X
		�ŏ��̒l
		�ړ����x(�b)
		�ő�l
�Ԃ�l�F�Ȃ�
===================================*/
void MoveSpriteNumber2D::Initialize(const int& textureKey,
									const int& firstNum,
									const float& moveSecondSpeed,
									const int& maxNum)
{

	//�摜�N���X�̏���������
	mpSpriteNumber2D->SetTextureKey(textureKey);
	mpSpriteNumber2D->Initialize();

	//�ړ������̏���������
	mpCountNumber->Initialize(firstNum, moveSecondSpeed, maxNum);
}

/*=================================
�X�V����
�����F�^�C�}�[
�Ԃ�l�F���݂̒l
===================================*/
int MoveSpriteNumber2D::Update(const DX::StepTimer& timer)
{
	mpCountNumber->Update(timer);

	return mpCountNumber->GetMoveNum();
}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void MoveSpriteNumber2D::Draw()
{
	//�摜�`��
	mpSpriteNumber2D->Create(mpCountNumber->GetMoveNum(), mDrawPosition);
	mpSpriteNumber2D->Draw();
}
