/*
�v���C�V�[�����烊�U���g�V�[���֏���n�����߂̃C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

class PtoRSceneComponent
{
private:
	//�������g
	static std::unique_ptr<PtoRSceneComponent> sPtoRComponent;

	//�X�R�A
	int mScoreNum;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	PtoRSceneComponent(const PtoRSceneComponent& pr) = delete;
	PtoRSceneComponent operator=(const PtoRSceneComponent& pr) = delete;


	//�R���X�g���N�^
	PtoRSceneComponent();
public:
	//���g�̃C���X�^���X
	static PtoRSceneComponent& GetPtoRIFInstance();


	//�X�R�A�̃A�N�Z�T
	void SetScoreNum(int score) { mScoreNum = score; }
	int GetScoreNum()const { return mScoreNum; }
};
