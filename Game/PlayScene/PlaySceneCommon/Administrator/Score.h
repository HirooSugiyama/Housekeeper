/*
�X�R�A�Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/06/28
*/
#pragma once


class Score
{
private:

	//�X�R�A��
	int mScore;

public:
	//�R���X�g���N�^
	Score()
		:mScore(0)
	{};
	//�f�X�g���N�^
	~Score()
	{
	};

	//�Q�[�W���̃A�N�Z�T
	int GetScoreNum()const { return mScore; }
	void SetScoreInit(const int& overwrite) { mScore = overwrite; }
	void SetScoreUp(const int& upnum) { mScore += upnum; }
	void SetScoreDown(const int& downnum) { mScore -= downnum; }

};
