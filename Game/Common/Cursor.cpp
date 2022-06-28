/*
�J�[�\�����Ǘ�����N���X
�쐬�ҁF���R
�쐬���F2021/10/13
*/
#include"pch.h"

#include"Cursor.h"

//�O���錾
#include"../Common/ObjectTexture.h"

/*=================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Cursor::Cursor()
	:
	mpCursorTexture(nullptr),
	mShiftNum(0.f),
	mSaveInitPosition(DirectX::SimpleMath::Vector2::Zero)
{
	mpCursorTexture = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
Cursor::~Cursor()
{
}

/*==================================
����������
�����F	�摜�̏������W�A�摜�g�嗦
		�ړ����A��]��[default 0.f]
�Ԃ�l�F�Ȃ�
===================================*/
void Cursor::Initialize(
	const int& key,
	const DirectX::SimpleMath::Vector2& initPosition,
	const DirectX::SimpleMath::Vector2& scale,
	const float& shiftPosition,
	const float& rot)
{
	//����������
	mpCursorTexture->Initialize();

	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto Textute = pRM->GetTexture(key);

	//�摜�̐ݒ�
	mpCursorTexture->SetTexture(Textute);

	//�g�嗦�̐ݒ�
	mpCursorTexture->SetPosition(initPosition);
	mSaveInitPosition = initPosition;

	//�g�嗦�̐ݒ�
	mpCursorTexture->SetScale(scale);

	//��]���̐ݒ�
	mpCursorTexture->SetRot(rot);

	//�ړ����̕ۑ�
	mShiftNum = shiftPosition;
}

/*=========================================
�`�揈��
�����F�`��t���O(true�ŕ`��)(default:true)
�Ԃ�l�F�Ȃ�
===========================================*/
void Cursor::Draw(const bool& flag)
{
	if (!flag)return;

	//�摜�̕`��
	mpCursorTexture->Draw();
}

/*=================================
�J�[�\������Ɉړ�����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Cursor::CursorUp()
{
	//��Ɉړ�������
	mpCursorTexture->SetPosition
	(
		mpCursorTexture->GetPosition() - 
		DirectX::SimpleMath::Vector2(0.f, mShiftNum)
	);
}

/*===================================
�J�[�\���������ʒu�Ƀ��Z�b�g����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Cursor::CursorReset()
{
	//��Ɉړ�������
	mpCursorTexture->SetPosition(mSaveInitPosition);
}

/*===================================
�J�[�\������ԉ��ɃZ�b�g����
�����F1��ʂ̍ő�X�e�[�W��
�Ԃ�l�F�Ȃ�
===================================*/
void Cursor::CursorSetUnder(const int& screenMaxStageNum)
{
	//���Ɉړ�������
	mpCursorTexture->SetPosition
	(
		mSaveInitPosition +
		DirectX::SimpleMath::Vector2(0.f, mShiftNum *(screenMaxStageNum +(Utility::EXCEPTION_NUM)))
	);
}

/*===================================
�J�[�\�������Ɉړ�����
�Ԃ�l�F�Ȃ�
===================================*/
void Cursor::CursorDown()
{
	//���Ɉړ�������
	mpCursorTexture->SetPosition(mpCursorTexture->GetPosition() + DirectX::SimpleMath::Vector2(0.f, mShiftNum));
}