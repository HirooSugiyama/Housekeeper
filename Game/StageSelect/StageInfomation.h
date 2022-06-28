/*
�e�X�e�[�W�̏����Ǘ�����N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

//�񋓌^�̎g�p
#include"StageNumer.h"
//����
#include"../Common/ObjectTexture.h"
#include"StageLevel.h"
#include "../Common/SpriteNumber/SpriteNumber2D.h"

class StageInfomation
{
private:

	//�t�@�C�����
	enum class FILE_INFO :int
	{
		TEXTURE_TAG,
		PHASE_NUM,
		LEVELOCITY,
	};

	//�X�e�[�W�摜�̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_INFO_TEXTURE_POSITION;

	//�X�e�[�W�摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 STAGE_INFO_TEXTURE_SCALE;

	//�X�e�[�W��Phase���̕`��ʒu
	static const DirectX::SimpleMath::Vector2 STAGE_INFO_PHASENUM_POSITION;

	//�X�e�[�W�����Ǘ�����CSV�t�@�C���̃p�X
	static const std::string STAGE_INFO_CSV_FILEPATH;



	//�X�e�[�W�摜
	std::unique_ptr<ObjectTexture> mpStageMapTexture;

	//�X�e�[�W���x��
	std::unique_ptr<StageLevel> mpStageLevel;

	//�X�e�[�W����ۑ�����ϐ�
	int mStageTextureTag[static_cast<int>(eSelectNum::NUM)];
	int mStagePhaseNum[static_cast<int>(eSelectNum::NUM)];
	int mStageLevelNum[static_cast<int>(eSelectNum::NUM)];

	//�t�F�[�Y���`��e�N�X�`��
	std::unique_ptr<SpriteNumber2D> mpPhaseSpriteNum;

public:

	//�R���X�g���N�^
	StageInfomation();
	//�f�X�g���N�^
	~StageInfomation();
	//����������
	void Initialize();
	//�`�揈��
	void Draw(const int& selectStageNum);

private:
	//�X�e�[�W�����t�@�C������擾����
	void LoadStageInfoCSV();

	//�L�[�ɉ����Đݒ�摜��ύX����
	int TextureSet(const std::string & fileKey);

};
