/*
�G��ǂݍ��ނ��߂̃N���X
�쐬�ҁF���R
�쐬���F2021/05/25
*/
#include"pch.h"
#include "EnemyCall.h"

/*========================
�R���X�g���N�^
�����F�Ȃ�
========================*/
EnemyCall::EnemyCall()
	:
	mNormalEnemyInfo(),
	mBossEnemyInfo()
{
}

/*===================================
�f�X�g���N�^
===================================*/
EnemyCall::~EnemyCall()
{
}


/*==============================
�G�����w�肷��֐�
�����F�t�@�C���̃p�X
�Ԃ�l�F�Ȃ�
==============================*/
void EnemyCall::LoadInfo(const std::string & filepath)
{
	//�����̓`���[�g���A����p�ǂݍ��݃N���X�Ȃ̂Ńt�@�C������ǂݍ���
	this->SetCSV(filepath);
}

/*=============================
�ۑ��p�ϐ���������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============================*/
void EnemyCall::Reset()
{
	mNormalEnemyInfo.resize(0);
}


/*==============================
�t�@�C���ǂݍ��ݏ����Fprivate
�����F�t�@�C���̃p�X
�Ԃ�l�F�Ȃ�
==============================*/
void EnemyCall::SetCSV(const std::string & filepath)
{
	//�񋓌^���ȑf��
	const int csv_position_x = static_cast<int>(eEnemyCSV::POSITION_X);
	const int csv_position_y = static_cast<int>(eEnemyCSV::POSITION_Y);
	const int csv_position_z = static_cast<int>(eEnemyCSV::POSITION_Z);
	const int phasenum = static_cast<int>(eEnemyCSV::PHASE_NUM);
	const int enemyType = static_cast<int>(eEnemyCSV::ENEMY_TYPE);

	//��O����
	Utility::FileError(filepath);

	//�t�@�C���ϊ�
	std::ifstream ifs(filepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;
	//�ꎞ�I�ɕۑ��p
	EnemyInfo instantPosition;

	//1�s�̓ǂݍ��ݏ���_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1�s�̏���stream�ɂ���
		std::stringstream lineStream(lineBuf);
		//1�}�X�̏��ۑ��p
		std::string tileBuf;

		//1�}�X�̏��ǂݍ��ݏ���
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//���W�̕ۑ�
			if (j == csv_position_x) {
				instantPosition.mVectorESPosition.x = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_position_y) {
				instantPosition.mVectorESPosition.y = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_position_z) {
				instantPosition.mVectorESPosition.z = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == phasenum) {
				instantPosition.mPhaseNumber = static_cast<int>(atoi(tileBuf.c_str()));
			}
			else if (j == enemyType) {
				instantPosition.mType = static_cast<EnemyType>(atoi(tileBuf.c_str()));
			}
		}

		if (instantPosition.mPhaseNumber != 0)
		{
			//��ނɂ���ď�����ς���
			switch (instantPosition.mType)
			{
				case EnemyType::NORMAL:
				{
					//�T�C�Y�𑝂₷
					mNormalEnemyInfo.push_back(instantPosition);

					break;
				}
				case EnemyType::BOSS:
				{
					mBossEnemyInfo = instantPosition;
					break;
				}
				default:
				{
					throw "Exception handling";
					break;
				}
			}
			instantPosition.mPhaseNumber = 0;
			instantPosition.mVectorESPosition = DirectX::SimpleMath::Vector3::Zero;
		}		
	}
}