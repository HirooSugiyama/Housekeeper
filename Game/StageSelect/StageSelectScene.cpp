/*
�X�e�[�W�I���V�[��
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include "pch.h"

#include "../GameMain.h"
#include "DeviceResources.h"

#include "StageSelectScene.h"


//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//Master�Ńt���O
#include"Game/Master.h"



//�^�O�̏������W
const DirectX::SimpleMath::Vector2 StageSelectScene::TAG_INIT_POSITION(113.f, 145.f);
//��
const float StageSelectScene::TAG_SHIFT = 100.f;
//�m�F��ʗp�J�[�\���̊�{���
//�g�嗦
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_SCALE(0.25f, 0.25f);
//�������W
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_INIT_POSITION(60.f, 150.f);
//�ړ���
const float StageSelectScene::SELECT_CURSOR_SHIFT = 100.f;

//��̈ʒu
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_POSITION(450.f,15.f);
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_SCALE(0.5f, 0.5f);

/*=========================================
�R���X�g���N�^
�����F�Ȃ�
=========================================*/
StageSelectScene::StageSelectScene()
	:
	mSelectNum(1),
	mpCursor(),
	mpStageInfo(),
	mpTag(),
	mpConfirmationScreen(),
	mpTextureBlinking(),
	mSelectFlag(false),
	mBGMID(Utility::EXCEPTION_NUM),
	mpCloud(nullptr),
	mpStageSelectNameTexture(nullptr),
	mpSignBoard(nullptr)
	

{
	mpCursor = std::make_unique<Cursor>();
	mpStageInfo = std::make_unique<StageInfomation>();
	mpConfirmationScreen = std::make_unique<ConfirmationScreen>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpCloud = std::make_unique<Cloud>();
	mpStageSelectNameTexture = std::make_unique<ObjectTexture>();
	mpSignBoard = std::make_unique<StageLevelSignBoard>();
	

	for (int i = 0; i< SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i] = std::make_unique<StageNumberTag>();
	}
}
/*========================================
�f�X�g���N�^
=========================================*/
StageSelectScene::~StageSelectScene()
{

}

/*=========================================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::Initialize()
{
	// ���\�[�X�֌W�̏����ݒ�
	//���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	auto pRM = ResourceManager::GetInstance();
	//�f�[�^������
	pRM->Finalize();
	//���\�[�X�̓ǂݍ���
	pRM->Load(ReadRange::STAGESELECT_TEXTURES_RESOUCE);

	//�X�e�[�W�ԍ��擾
#ifdef MASTER
	//�X�e�[�W�ԍ����ő�ԍ���
	mSelectNum = static_cast<int>(eSelectNum::_1);
	mMaxSelectStageNumber = static_cast<int>(eSelectNum::NUM) - 1;
#else
	//�I������ԍ��̓t�@�C������擾
	mSelectNum = this->GetFirstSelectStageNum();
	mMaxSelectStageNumber = this->GetFirstSelectStageNum();
#endif

	// �e�N�X�`���̓ǂݍ���
	mpTexture = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGESELECT));

	mpStageSelectNameTexture->SetTexture(pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGESELECTNAME)));
	mpStageSelectNameTexture->Initialize();
	mpStageSelectNameTexture->SetPosition(NAME_POSITION);
	mpStageSelectNameTexture->SetScale(NAME_SCALE);

	//�J�[�\���̏���������
	mpCursor->Initialize(
		static_cast<int>(StageSelectTexturesResouce::TEXTURE__CURSOR),
		SELECT_CURSOR_INIT_POSITION,
		SELECT_CURSOR_SCALE,
		SELECT_CURSOR_SHIFT);

	//�X�e�[�W�e����̏���������
	mpStageInfo->Initialize();

	for (int i = 0;  i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->Initialize();
	}
	//�m�F��ʂ̏���������
	mpConfirmationScreen->Initialize(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STRINGJAPANISE));

	//�Ȃ𗬂�
	this->PlayBGM();

	//�_�̏���������
	mpCloud->Initialize(static_cast<int>(StageSelectTexturesResouce::TEXTURE__CLOUD));

	//�Ŕ̏����ݒ�
	mpSignBoard->Initialize();

	//�}�X�^�[�łłȂ��Ƃ��̂ݏ�����ʂ�
#ifndef MASTER

	//�J�[�\���̈ʒu��ݒ肷��
	int shiftNum = 0;
	if (mSelectNum >= static_cast<int>(eSelectNum::_7))
	{
		shiftNum = mSelectNum - static_cast<int>(eSelectNum::_6);
	}
	else
	{
		shiftNum = mSelectNum;
	}
	for (int i = 1; i < shiftNum; i++)
	{
		mpCursor->CursorDown();
	}
#else
	//�J�[�\���̈ʒu��ݒ肷��
	int shiftNum = 0;

	//�t�@�C������Ō�ɗV�񂾔ԍ����擾
	mSelectNum = this->GetFirstSelectStageNum();

	if (mSelectNum >= static_cast<int>(eSelectNum::_7))
	{
		shiftNum = mSelectNum - static_cast<int>(eSelectNum::_6);
	}
	else
	{
		shiftNum = mSelectNum;
	}

	for (int i = 1; i < shiftNum; i++)
	{
		mpCursor->CursorDown();
	}


#endif

	//�X�e�[�W�ԍ���ݒ肷��
	this->SetNumberTag();

}

/*=========================================
�X�V
����	�F�^�C�}�[�̃w���p�[�֐�
�߂�l	�F���̃V�[���ԍ�
=========================================*/
eGameScene StageSelectScene::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//�X�e�[�W�I��
	this->StageSelect();

	//�_�ŏ���
	mpTextureBlinking->Update();

	//�_�̍X�V����
	mpCloud->Update();

	//�I����ʂȂ�
	if (mSelectFlag)
	{
		//�m�F��ʂ̍X�V����
		bool timerFlag = mpConfirmationScreen->Update();

		//�܂����ԂłȂ���Ώ��������Ȃ�
		if (!timerFlag)	return eGameScene::NONE;

	}
	


	if (pKey->Decision()|| pGamePad->Decision())		//����
	{	
		//�m�F��ʂȂ��
		if (mSelectFlag)
		{
			if (mpConfirmationScreen->GetSelectFlag())
			{
				//�v���C�V�[����
				//�X�e�[�W�I����ʂ���̏�񋤗L�Ǘ��N���X�̎擾
				auto& pStoP = StoPSceneComponent::GetStoPIFInstance();

				pStoP.SetStageCSV(this->SetFileName());
				//�X�e�[�W�ԍ��������ɕۑ����Ă���
				pStoP.SetStageNumber(std::to_string(mSelectNum));

				ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
				//�Ȃ��~�߂�
				this->StopBGM();

				auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
				pSTI.SetFadeUseFlag(true);
				pSTI.GetFade()->SetClose();

				return eGameScene::PLAY;	//���ڃv���C�V�[����
			}
			else
			{
				//�m�F��ʗp�J�[�\���̃^�C�}�[�����Z�b�g����
				mpConfirmationScreen->Reset();

				//�m�F�p��ʂ�����
				mSelectFlag = false;
			}
			
		}
		else
		{

			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
			mSelectFlag = true;

			//���Z�b�g����
			mpConfirmationScreen->Reset();
		}		
	}

	return eGameScene::NONE;
}

/*=======================================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::Draw()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	//�`��J�n
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);
	
	DirectX::SimpleMath::Vector2 position{ 0.f,0.f };

	//�w�i�摜�̕`��
	pDxIF.GetSpriteBatch()->Draw(mpTexture.Get(), position);

	//�Ŕ̕`��
	mpSignBoard->Draw();

	//�_�̕`�揈��
	mpCloud->Draw();

	//��̕`��
	mpStageSelectNameTexture->Draw();
	

	//�I����ʂł͂Ȃ��Ȃ�
	if (!mSelectFlag)
	{
		//�J�[�\���̕`��
		mpCursor->Draw();

		//�X�e�[�W���̕`��
		mpStageInfo->Draw(mSelectNum);

		//�X�e�[�W�ԍ������ۑ�
		int stageScreenNum = mSelectNum;
		//����2��ʖڈȍ~�̃X�e�[�W�Ȃ�
		if (stageScreenNum >= static_cast<int>(eSelectNum::_7))
		{
			//1��ʕ��l�����炷
			stageScreenNum -= static_cast<int>(eSelectNum::_6);
		}

		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//���ݑI���ł��Ȃ��X�e�[�W�͏���
			if (i >= mMaxSelectStageNumber)continue;

			//�I�����Ă���X�e�[�W�̂ݓ_�ł�����
			if (stageScreenNum - 1 == i)
			{
				
				mpTag[i]->Draw(mpTextureBlinking->GetBlinkingFlag());
			}
			else
			{
				//����ȊO�͒ʏ�`��
				mpTag[i]->Draw();
			}
		}
	}
	else
	{
		//�J�[�\���̕`��
		mpCursor->Draw();

		//�X�e�[�W���̕`��
		mpStageInfo->Draw(mSelectNum);
		//�e�X�e�[�W�ԍ��̕`��
		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//���ݑI���ł��Ȃ��X�e�[�W�͏���
			if (i >= mMaxSelectStageNumber)continue;

			//����ȊO�͒ʏ�`��
			mpTag[i]->Draw();
		}
		mpConfirmationScreen->Draw(mpTextureBlinking->GetBlinkingFlag());
	}

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::Finalize()
{
	const auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();
}


/*=========================================
���[�h�I��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::StageSelect()
{
	//�I����ʂȂ珈�����s��Ȃ�
	if (mSelectFlag)return;

	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver() || pGamePad->ChangeCursorUp())
	{
		//�J�[�\�����グ��
		this->CursorUp();
	}

	if (pKey->SelectUnder() || pGamePad->ChangeCursorDown())
	{
		//�J�[�\����������
		this->CursorDown();
	}
}


/*=========================================
�t�@�C�����Z�o:private
�����F�Ȃ�
�Ԃ�l�F�t�@�C���̑��΃p�X
=========================================*/
std::string StageSelectScene::SetFileName()
{
	std::string filePath = "Resources/CSV/";
	std::string fileName = "PlayScene" + std::to_string(mSelectNum);
	std::string expand = ".csv";
	std::string fullFilePath="none";

	fullFilePath = filePath + fileName + expand;
	return fullFilePath;
}

/*=========================================
�J�[�\����������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::CursorUp()
{
	//�ő�X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
	if (mSelectNum - 1 != static_cast<int>(eSelectNum::NONE))
	{
		//�摜�����
		mpCursor->CursorUp();
		mSelectNum--;
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//��ʂň�ԏ�̑I�����ɂȂ�����J�[�\���ʒu�����Z�b�g����
	if (mSelectNum == static_cast<int>(eSelectNum::_7))
	{
		mpCursor->CursorReset();
		//�X�e�[�W�ԍ���ۑ�����
		this->SetNumberTag();
	}
	//��ʂň�ԉ��̑I�����ɂȂ�����w��̈ʒu�ɃJ�[�\�����Z�b�g����
	if (mSelectNum == static_cast<int>(eSelectNum::_6))
	{
		mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
		//�X�e�[�W�ԍ���ۑ�����
		this->SetNumberTag();
	}
}

/*=========================================
�J�[�\����������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::CursorDown()
{
	//�ŏ��X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
	if (mSelectNum + 1 != static_cast<int>(eSelectNum::NUM) && mSelectNum + 1 <= mMaxSelectStageNumber)
	{
		//�摜������
		mpCursor->CursorDown();
		mSelectNum++;
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//��ʂň�ԏ�̑I�����ɂȂ�����J�[�\���ʒu�����Z�b�g����
	if (mSelectNum == static_cast<int>(eSelectNum::_7))
	{
		mpCursor->CursorReset();
		//�X�e�[�W�ԍ���ۑ�����
		this->SetNumberTag();
	}
	//��ʂň�ԉ��̑I�����ɂȂ�����w��̈ʒu�ɃJ�[�\�����Z�b�g����
	if (mSelectNum == static_cast<int>(eSelectNum::_6))
	{
		mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
		//�X�e�[�W�ԍ���ۑ�����
		this->SetNumberTag();
	}
}

/*========================================
�ԍ���ݒ肷��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::SetNumberTag()
{
	int index = 0;
	int stagenum = 0;
	//���Z�b�g����
	for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->SetStageNum(Utility::EXCEPTION_NUM);
	}
	
	//�㔼���Ȃ�
	if (mSelectNum <= static_cast<int>(eSelectNum::_6))
	{
		stagenum = static_cast<int>(eSelectNum::_1);
	}
	else 
	{
		stagenum = static_cast<int>(eSelectNum::_7);
	}

	//���Z�b�g����
	for (index; index < SCREEN_STEGE_MAX_NUM; index++,stagenum++)
	{
		//�}�X�^�[�łłȂ��Ƃ��̂ݏ�����ʂ�
#ifndef MASTER
		if (stagenum  > this->GetFirstSelectStageNum())
		{
			break;
		}
#else
		if (stagenum > static_cast<int>(eSelectNum::NUM) - 1)
		{
			break;
		}
#endif
		mpTag[index]->SetStageNum(stagenum);

		mpTag[index]->SetPosition(TAG_INIT_POSITION+ DirectX::SimpleMath::Vector2(0.f,(index *TAG_SHIFT)));

	}

}

/*=========================================
�X�e�[�W�ԍ��擾:private
�����F�Ȃ�
�Ԃ�l�F�X�e�[�W�ԍ�
=========================================*/
int StageSelectScene::GetFirstSelectStageNum()
{
	//��O����
	Utility::FileError(Utility::NEXT_STAGE_NUM_FILEPATH);

	//�t�@�C���ϊ�
	std::ifstream ifs(Utility::NEXT_STAGE_NUM_FILEPATH);
	//1�����̏���ۑ�����ϐ�
	std::string stageNum{};

	//�Ăяo��
	std::getline(ifs, stageNum);

	return atoi(stageNum.c_str());
}

/*=========================================
���y�𗬂�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_STAGESELECT);
}

/*=========================================
���y���~�߂�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void StageSelectScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
