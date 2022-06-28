/*
�������Ǘ��t�@�C��
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include"pch.h"
#include"Money.h"


//�N���X�O���ŏ�����
std::unique_ptr<Money> Money::sMoney = nullptr;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Money::Money()
	:
	mFilepath("none"),
	mPossessionMoney()
{
}

/*=================================
���g�̃C���X�^���X
�����F�Ȃ�
�Ԃ�l�F���g�̃C���X�^���X
===================================*/
Money& Money::GetMoneyInstance()
{
	if (sMoney == nullptr)
	{
		sMoney.reset(new Money());
	}
	return *sMoney;
}

/*=================================
�t�@�C�����̐ݒ�
�����F�t�@�C���p�X
�Ԃ�l�F�Ȃ�
===================================*/
void Money::LoadFileSet(std::string filepath)
{
	//�����̕ۑ�
	mFilepath = filepath;

	//���z�̏����ݒ�
	this->MoneyInit();
}

/*===================================
�������̏����ݒ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Money::MoneyInit()
{
	//��O����
	Utility::FileError(mFilepath);

	//�t�@�C���ϊ�
	std::ifstream ifs(mFilepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//�����o��
	std::getline(ifs, lineBuf);


	mPossessionMoney = static_cast<int>(atof(lineBuf.c_str()));
}

