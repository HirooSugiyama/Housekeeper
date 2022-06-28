/*
���U���g�Ŏg�p�������ǂݍ��݁A�Ǘ�����N���X
�쐬�ҁF���R
�쐬���F2021/10/23
*/
#include"pch.h"

#include"ResultInfo.h"


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
ResultInfo::ResultInfo()
	:
	mScoreRanking{},
	mFilePath("none")
{
}

/*===================================
�f�X�g���N�^
===================================*/
ResultInfo::~ResultInfo()
{
}

/*===================================
����������
�����F�X�e�[�W�ԍ�
�Ԃ�l�F�Ȃ�
===================================*/
void ResultInfo::Initialize(const int& stagenum)
{
	//�t�@�C�����쐬
	std::string filetop = "SaveData/Stage",
		filebottom = "Score.csv";

	mFilePath = filetop + std::to_string(stagenum) + filebottom;

	
	//�t�@�C���ǂݍ���
	this->LoadScoreRanking();


}

/*===================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ResultInfo::Update()
{

}

/*==================================
�X�R�A�����L���O�ǂݍ���
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ResultInfo::LoadScoreRanking()
{
	//��O����
	Utility::FileError(mFilePath);

	//�t�@�C���ϊ�
	std::ifstream ifs(mFilePath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//�X�R�A�����L���O�̃X�R�A��ۑ�
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		std::getline(ifs, lineBuf);
		//�X�R�A��ۑ�
		mScoreRanking[i] = atoi(lineBuf.c_str());
	}
}

/*==================================
�X�R�A�����L���O�ǂݍ���
�����F�X�R�A�l
�Ԃ�l�F�Ȃ�
===================================*/
void ResultInfo::SetScoreRanking(const int& scorenum)
{
	//�Ǘ��p�ϐ��̐錾
	int instantScoreRanking[ResultDrawStringConstant::SCORE_RANKING_STORAGE]{0,0,0,0,0};
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		instantScoreRanking[i] = mScoreRanking[i];
	}

	int j = 0;
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++,j++)
	{
		//�����擾�����X�R�A�̂ق�������������
		if (instantScoreRanking[i] < scorenum&&i==j)
		{
			mScoreRanking[i] = scorenum;
			j--;
		}
		else
		{
			mScoreRanking[i] = instantScoreRanking[j];
		}

	}
}

/*==================================
�X�R�A����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ResultInfo::WriteScore()
{
	//���݂̋��z���t�@�C���ɕۑ�����
	std::ofstream writingFile;
	writingFile.open(mFilePath, std::ios::out);


	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		writingFile << mScoreRanking[i] << std::endl;
	}

	writingFile.close();

}