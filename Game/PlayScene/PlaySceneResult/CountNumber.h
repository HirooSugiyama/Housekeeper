/*
��������
�쐬�ҁF���R
�쐬���F2021/10/13
*/
#pragma once





namespace DX
{
	class StepTimer;
}

class CountNumber
{
private:

	//�����l
	float mFirstNum;

	//�ő�l(��������)
	int mTopNum;

	//������
	float mVelocityNum;

	//1�b������̑�����
	float mOneSecondVelocityNum;


public:

	//�R���X�g���N�^
	CountNumber();
	//�f�X�g���N�^
	~CountNumber();
	//����������
	void Initialize(int firstNum, float moveSecondSpeed, int maxNum);
	//�X�V����
	int Update(const DX::StepTimer& timer,bool fallflag=false);

	//���݂̐��l�̃A�N�Z�T
	int GetMoveNum() const { return static_cast<int>(mFirstNum); }

	//�w��̒l�ɋ����ύX
	void ForcedChangeMoveNum() { mFirstNum = static_cast<float>(mTopNum); }

};
