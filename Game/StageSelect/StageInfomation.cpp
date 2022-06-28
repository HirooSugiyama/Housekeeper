/*
�e�X�e�[�W�̏����Ǘ�����N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include"pch.h"

#include"StageInfomation.h"

//�X�e�[�W�摜�̍��W
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_POSITION(655.f,144.f);

//�X�e�[�W�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_SCALE(0.43f,0.36f);

//�X�e�[�W��Phase���̕`��ʒu
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_PHASENUM_POSITION(860.f, 525.f);

//�X�e�[�W�����Ǘ�����CSV�t�@�C���̃p�X
const std::string StageInfomation::STAGE_INFO_CSV_FILEPATH =
	"Resources/CSV/StageInfomation.csv";


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
StageInfomation::StageInfomation()
	:
	mpStageMapTexture(),
	mpStageLevel(),
	mStageTextureTag{},
	mStagePhaseNum{},
	mStageLevelNum{}
{
	mpStageMapTexture = std::make_unique<ObjectTexture>();
	mpStageLevel = std::make_unique<StageLevel>();
	mpPhaseSpriteNum = std::make_unique<SpriteNumber2D>();
	//�t�@�C���ǂݍ���
	this->LoadStageInfoCSV();
}

/*===================================
�f�X�g���N�^
===================================*/
StageInfomation::~StageInfomation()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void StageInfomation::Initialize()
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__CURSOR));
	//�摜����������
	mpStageMapTexture->Initialize();

	//�摜��ݒ肷��
	mpStageMapTexture->SetTexture(textute);

	//�g�嗦�̐ݒ�
	mpStageMapTexture->SetPosition(STAGE_INFO_TEXTURE_POSITION);

	//�g�嗦�̐ݒ�
	mpStageMapTexture->SetScale(STAGE_INFO_TEXTURE_SCALE);

	//�X�e�[�W���x���Ǘ��N���X�̏���������
	mpStageLevel->Initialize();

	//�X�R�A�̃t�H���g���w��
	mpPhaseSpriteNum->SetTextureKey(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGENUMBERFONT));
	mpPhaseSpriteNum->Initialize();
	mpPhaseSpriteNum->SetAlign(eAlign::LEFT);
	mpPhaseSpriteNum->SetScale(Utility::STRING_SIZE_SMALL);
}


/*===================================
�`�揈��
�����F�I�����Ă���X�e�[�W�ԍ�
�Ԃ�l�F�Ȃ�
===================================*/
void StageInfomation::Draw(const int& selectStageNum)
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(mStageTextureTag[selectStageNum]);
	//�摜��ݒ肷��
	mpStageMapTexture->SetTexture(textute);
	mpStageMapTexture->Draw();

	//�X�e�[�W���x���Ǘ��N���X�̕`�揈��
	int starnum = mStageLevelNum[selectStageNum];
	mpStageLevel->Draw(starnum);


	//�t�F�[�Y���̕`��
	mpPhaseSpriteNum->Create(mStagePhaseNum[selectStageNum], STAGE_INFO_PHASENUM_POSITION);
	mpPhaseSpriteNum->Draw();
}

/*===================================
�X�e�[�W�����t�@�C������擾����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void StageInfomation::LoadStageInfoCSV()
{
	//��O����
	Utility::FileError(STAGE_INFO_CSV_FILEPATH);

	//�t�@�C���ϊ�
	std::ifstream ifs(STAGE_INFO_CSV_FILEPATH);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

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
			//�X�e�[�W�摜�̃^�O��ۑ�
			if (j == static_cast<int>(FILE_INFO::TEXTURE_TAG))
			{
				mStageTextureTag[i] = this->TextureSet(tileBuf);	
			}
			//�t�F�[�Y�ԍ���ۑ�
			if (j == static_cast<int>(FILE_INFO::PHASE_NUM))
			{
				mStagePhaseNum[i] = atoi(tileBuf.c_str());
			}
			//�t�F�[�Y�̃��x����ۑ�
			if (j == static_cast<int>(FILE_INFO::LEVELOCITY))
			{
				mStageLevelNum[i] = atoi(tileBuf.c_str());
			}
		}
	}
}

/*===================================
�L�[�ɉ����Đݒ�摜��ύX����:private
�����F�擾�����t�@�C���̃L�[
�Ԃ�l�F���\�[�X�ԍ�
===================================*/
int StageInfomation::TextureSet(const std::string & fileKey)
{
	if (fileKey == "Stage1")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE1);
	}
	else if (fileKey == "Stage2")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE2);
	}
	else if (fileKey == "Stage3")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE3);
	}
	else if (fileKey == "Stage5")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE5);
	}
	else if (fileKey == "Stage6")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE6);
	}
	else if (fileKey == "Stage7")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE7);
	}
	else if (fileKey == "Stage8")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE8);
	}
	else if (fileKey == "Stage9")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE9);
	}
	else if (fileKey == "Stage10")
	{
		return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE10);
	}

	return static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGE1);
}




