/*
�Q�[�����C��
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include "pch.h"

#include "DeviceResources.h"
#include "GameMain.h"


#include "Game/TitleScene/TitleScene.h"
#include "Game/StageSelect/StageSelectScene.h"
#include "Game/PlayScene/PlayScene.h"

//�e��V�[���C���^�[�t�F�[�X
#include"Game/Component/SceneComponent/PtoRSceneComponent.h"
#include"Game/Component/SceneComponent/StoPSceneComponent.h"


//�������̎擾
#include"Money/Money.h"
#include"Libraries/MyLibraries/Adx2.h"

//�Q�[���p�b�h�A�C�R��
//���W
const DirectX::SimpleMath::Vector2 GameMain::GAMEPAD_ICON_POSITION(0.f,0.f);
//�g�嗦
const DirectX::SimpleMath::Vector2 GameMain::GAMEPAD_ICON_SCALE(0.f,0.f);


/*=========================================
�R���X�g���N�^
�����F�Ȃ�
=========================================*/
GameMain::GameMain()
	: 
	mNextScene(eGameScene::TITLE),		// �����V�[���̐ݒ�
	mpScene(nullptr)
{
}


/*=========================================
�f�X�g���N�^
=========================================*/
GameMain::~GameMain()
{
	this->Finalize();

	// �T�E���h�̏I������
	ADX2::GetInstance().Finalize();
}


/*=========================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::Initialize()
{
	// �T�E���h�̏�����
	ADX2::GetInstance().Initialize
	("Resources/Audio/Housekeeper_Sound.acf", "Resources/Audio/CueSheet_0.acb");

	//���C�v����
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.GetWipe()->Initialize();
	pSTI.GetFade()->Initialize();


	// �V�[���쐬
	this->CreateScene();

}

/*=========================================
�X�V
�����F�^�C�}�[
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::Update(const DX::StepTimer& timer)
{
	//�L�[�{�[�h�̍X�V����
	this->KeyboardUpdate();

	//�Q�[���p�b�h�̍X�V����
	this->GamePadUpdate();
	
	//�^�C�}�[�̍X�V
	auto& pTM = TimerComponent::GetTimerInstance();
	pTM.SetTimer(timer);

	//���C�v����
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	bool flag{ false };
	if (pSTI.GetWipeUseFlag())
	{
		flag = pSTI.GetWipe()->Update(static_cast<float>(pTM.GetTimer().GetElapsedSeconds()));
		if (flag)pSTI.SetWipeUseFlag(false);
	}
	else if (pSTI.GetFadeUseFlag())
	{
		//�t�F�[�h����
		flag = pSTI.GetFade()->Update(static_cast<float>(pTM.GetTimer().GetElapsedSeconds()));
		if (flag)pSTI.SetFadeUseFlag(false);
	}
	
	

	//���C�v���Ȃ珈�������Ȃ�
	if (pSTI.GetWipeUseFlag())return;

	//�t�F�[�h�C�����Ȃ珈�������Ȃ�
	if (pSTI.GetFadeUseFlag()&&!pSTI.GetFade()->GetFlagOpen())return;

	// ���̃V�[�����ݒ肳��Ă�����V�[���؂�ւ�
	if (mNextScene != eGameScene::NONE)
	{
		// �V�[���폜
		DeleteScene();

		//���\�[�X�}�l�[�W���̓��e�̍폜
		auto pRM = ResourceManager::GetInstance();
		pRM->Finalize();//�������̉��


	
		// �V�[���쐬
		CreateScene();
	}
	
	// ���Ԃ�����΍X�V
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update();
	}

}


/*=========================================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::Render()
{
	// ���Ԃ�����Ε`��
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}

	//���C�v����
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.GetWipe()->Draw();
	pSTI.GetFade()->Draw();
}


/*=========================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::Finalize()
{
	this->DeleteScene();
	//���\�[�X�֌W�̏����ݒ�
	//���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	auto pRM = ResourceManager::GetInstance();
	//�f�[�^������
	pRM->Finalize();
}

/*=========================================
�V�[���̍쐬:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::CreateScene()
{
	// �V�[�����쐬����Ă���Ƃ��͏������Ȃ�
	if (mpScene != nullptr)
	{
		return;
	}

	// ���V�[���̍쐬
	switch (mNextScene)
	{
		case eGameScene::TITLE:
		{
			mpScene = std::make_unique<TitleScene>();
			break;
		}
		case eGameScene::STAGE_SELECT:
		{
			mpScene = std::make_unique<StageSelectScene>();
			break;
		}
		case eGameScene::PLAY:
		{
			mpScene = std::make_unique<PlayScene>();
			break;
		}
		default:
		{
			throw "Exception handling";
			break;
		}
	}

	// �쐬�����V�[����������
	mpScene->Initialize();

	//���ւ�Scene����������
	mNextScene = eGameScene::NONE;
}

/*=========================================
�V�[���̍폜�Fprivate
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::DeleteScene()
{
	// �V�[�����쐬����Ă��Ȃ���Ώ������Ȃ�
	if (mpScene == nullptr)
	{
		return;
	}

	// ���V�[���̏I������
	mpScene->Finalize();

	// ���V�[���̍폜
	if (mpScene)
	{
		mpScene.reset();
	}
}

/*=========================================
�L�[�{�[�h�̍X�V����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::KeyboardUpdate()
{
	//�g���b�J�[�̎擾
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	pKey->KeyUpdate();
}

/*=========================================
�Q�[���p�b�h�̍X�V����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void GameMain::GamePadUpdate()
{
	//�g���b�J�[�̎擾
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();
	pGamePad->ButtonUpdate();
}
