/*
�X�e�[�W�Z���N�g��ʂ���v���C�V�[���֏���n�����߂̃C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

class StoPSceneComponent
{
private:
	//�������g
	static std::unique_ptr<StoPSceneComponent> sStoPComponent;


	//�ǂݍ��ރX�e�[�WCSV�t�@�C��
	std::string mCSVFileName;

	//�X�e�[�W�ԍ�
	std::string mStageNumber;	//��XString�^�Ŏg�p���邽�߂��炩����String�^�ŏ���

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	StoPSceneComponent(const StoPSceneComponent& dr) = delete;
	StoPSceneComponent operator=(const StoPSceneComponent& dr) = delete;

	//�R���X�g���N�^
	StoPSceneComponent();
public:
	//���g�̃C���X�^���X
	static StoPSceneComponent& GetStoPIFInstance();


	//�e��A�N�Z�T
	//CSV�t�@�C��
	void SetStageCSV(const std::string& filepath) { mCSVFileName = filepath; }
	std::string GetStageCSV() const { return mCSVFileName; }

	//�X�e�[�W�ԍ�
	void SetStageNumber(const std::string& number) { mStageNumber = number; }
	std::string GetStageNumber()const { return mStageNumber; }
};
