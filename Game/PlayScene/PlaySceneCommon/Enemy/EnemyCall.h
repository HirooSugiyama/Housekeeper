/*
�G��ǂݍ��ނ��߂̃N���X
�쐬�ҁF���R
�쐬���F2021/05/25
*/
#pragma once

//�񋓌^�̎g�p
#include"EnemyType.h"


class EnemyCall
{
private:
	//���W���
	enum class eEnemyCSV :int
	{
		POSITION_X,		//X���W
		POSITION_Y,		//Y���W
		POSITION_Z,		//Z���W
		PHASE_NUM,		//�����o���t�F�[�Y��
		ENEMY_TYPE,		//�G�̎��
	};

	//�G���
	struct EnemyInfo
	{
		//�G�̍��W
		DirectX::SimpleMath::Vector3 mVectorESPosition;	//1,2,3�Ԗڂ̗v�f
		//�t�F�[�Y�ԍ�
		int mPhaseNumber;
		//�G�̎��
		EnemyType mType;

		//�R���X�g���N�^
		EnemyInfo()
			:mVectorESPosition()
			, mPhaseNumber()
			, mType(EnemyType::NONE)
		{}
	};
	//�萔

	//���̉�
	std::vector<EnemyInfo> mNormalEnemyInfo;	//�ʏ�G���̓X�e�[�W�ɂ���ĉ�
	EnemyInfo mBossEnemyInfo;					//�{�X�G�̓X�e�[�W�ɍő�1��

public:
	//�R���X�g���N�^
	EnemyCall();
	//�f�X�g���N�^
	~EnemyCall();
	//�t�@�C������Ԃ�
	EnemyInfo GetNormalEnemyStructer(const int& i)const {return mNormalEnemyInfo[i];}
	EnemyInfo GetBossEnemyStructer()const {return mBossEnemyInfo;}
	//�v�f����Ԃ�
	int GetNormalEnemyStructerSize() const {return mNormalEnemyInfo.size();}
	//�G�����w�肷��֐�
	void LoadInfo(const std::string & filepath);
	//�v�f��������
	void Reset();

private:
	//CSV�t�@�C�������w��
	void SetCSV(const std::string & filepath);
};