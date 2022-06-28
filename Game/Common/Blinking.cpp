/*
�_�ŏ��������N���X
�쐬�ҁF���R
�쐬���F2021/11/01
*/
#include"pch.h"

#include"Blinking.h"


/*===================================
�R���X�g���N�^
�����F�_�Ŏ���
===================================*/
Blinking::Blinking(float intervalNum)
	:
	mBlinkingFlag(false),
	mSinfNum(0.f),
	mBlinkingInterval(intervalNum),
	mBlinkingNum(0.f)
{
}

/*===================================
�f�X�g���N�^
===================================*/
Blinking::~Blinking()
{
}
/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Blinking::Update()
{

	mBlinkingNum += mBlinkingInterval;
	mSinfNum = std::sinf(mBlinkingNum);

	//sin�l�����ƂɃt���O�����Ă�
	if (mSinfNum >= 0)
	{
		mBlinkingFlag = true;
	}
	else
	{
		mBlinkingFlag = false;
	}
}