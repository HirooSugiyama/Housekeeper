/*
�^�C�g���V�[��
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include "pch.h"

#include "../GameMain.h"
#include "DeviceResources.h"
#include "TitleScene.h"
#include"Game/Common/Cloud.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"

//���S�̍��W
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_LOGO_POSITION(190.f, 160.f);
//�J�n�{�^���ʒu
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_START_BAR_POSITION(450.f,450.f);


//�^�C�g���o�[�����؂���ʒu
const RECT TitleScene::TITLE_BAR_INIT_RECT{ 0,0,396,143 };

/*=======================================
�R���X�g���N�^
�����F�Ȃ�
=========================================*/
TitleScene::TitleScene()
	:
	mpCloud(),
	mBGMID(Utility::EXCEPTION_NUM),
	mpTitleBar(nullptr)
{
	//�_�̐���
	mpCloud = std::make_unique<Cloud>();
	mpTitleBar = std::make_unique<ObjectSpriteTexture>();
}

/*=========================================
�f�X�g���N�^
=========================================*/
TitleScene::~TitleScene()
{
}

/*=========================================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void TitleScene::Initialize()
{
	// ���\�[�X�֌W�̏����ݒ�
	//���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	auto pRM = ResourceManager::GetInstance();
	//�f�[�^������
	pRM->Finalize();
	//���\�[�X�̓ǂݍ���
	pRM->Load(ReadRange::TITLE_TEXTURES_RESOUCE);

	// �e�N�X�`���̓ǂݍ���
	mpTexture = pRM->GetTexture(static_cast<int>(TitleTexturesResouce::TEXTURE__TITLE_BACKGROUND));
	mpLogo = pRM->GetTexture(static_cast<int>(TitleTexturesResouce::TEXTURE__TITLENAME));
	
	//�����_�̏���������
	mpCloud->Initialize(static_cast<int>(TitleTexturesResouce::TEXTURE__CLOUD));

	auto texture= pRM->GetTexture(static_cast<int>(TitleTexturesResouce::TEXTURE__TITLEBAR));
	mpTitleBar->SetTexture(texture);
	mpTitleBar->Initialize();
	mpTitleBar->SetPosition(TITLE_START_BAR_POSITION);
	mpTitleBar->SetRect(TITLE_BAR_INIT_RECT);

	//BGM�𗬂�
	this->PlayBGM();
}

/*=========================================
�X�V
����	�F�^�C�}�[�̃w���p�[�֐�
�߂�l	�F���̃V�[���ԍ�
=========================================*/
eGameScene TitleScene::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//�_�̍X�V����
	mpCloud->Update();

	//���͋@�픻�菈��
	this->ChangeControl();

	// �T�E���h�̍X�V
	ADX2::GetInstance().Update();

	if (pKey->Decision()|| pGamePad->Decision())//�L�[���͂��s��ꂽ��
	{
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
		//�Ȃ��~�߂�
		this->StopBGM();
		return eGameScene::STAGE_SELECT;//���̃V�[����
	}

	return eGameScene::NONE;
}

/*=========================================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void TitleScene::Draw()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	//�`��J�n
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);

	pDxIF.GetSpriteBatch()->Draw(mpTexture.Get(), DirectX::SimpleMath::Vector2::Zero);
	
	mpCloud->Draw();
	mpTitleBar->Draw();

	pDxIF.GetSpriteBatch()->Draw(mpLogo.Get(), TITLE_LOGO_POSITION);
	

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void TitleScene::Finalize()
{
	// ���\�[�X�֌W�̏�����
	auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();
}

/*========================================
�Q�[���p�b�h�ƃL�[��؂�ւ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void TitleScene::ChangeControl()
{
	//�Q�[���p�b�h�g�p�󋵂��擾
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	RECT rect = TITLE_BAR_INIT_RECT;

	//�g�p���̏���
	if (pGamePadTracker->GetUseFlag())
	{
		rect.top = TITLE_BAR_INIT_RECT.bottom;
		rect.bottom *= Utility::SHIFT_SPRITE_TEXTURE;
		mpTitleBar->SetRect(rect);
	}
	//�p�b�h���g�p���̏���
	else
	{
		mpTitleBar->SetRect(rect);
	}
}

/*========================================
���y�𗬂�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void TitleScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_TITLE);
}

/*=========================================
���y���~�߂�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void TitleScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
