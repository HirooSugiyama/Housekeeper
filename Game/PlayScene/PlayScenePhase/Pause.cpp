/*
�|�[�Y
�쐬�ҁF���R
�쐬���F2021/09/30
*/

#include"pch.h"
#include"Pause.h"

//������
#include"../PlayScene.h"
#include"../../UI/UI.h"

//�g�嗦
const DirectX::SimpleMath::Vector2 Pause::SELECT_CURSOR_SCALE(0.25f, 0.25f);
//�������W
const DirectX::SimpleMath::Vector2 Pause::SELECT_CURSOR_INIT_POSITION(570.f, 445.f);
//�ړ���
const float Pause::SELECT_CURSOR_SHIFT = 108.f;

//�����`��ʒu
const DirectX::SimpleMath::Vector2 Pause::SELECT_STRING_ON_POS(923, 305);

const DirectX::SimpleMath::Vector2 Pause::SELECT_STRING_SLASH_POS = SELECT_STRING_ON_POS + 
													DirectX::SimpleMath::Vector2(110.f, 0.f);

const DirectX::SimpleMath::Vector2 Pause::SELECT_STRING_OFF_POS = SELECT_STRING_SLASH_POS +
													DirectX::SimpleMath::Vector2(40.f, 0.f);

/*=====================
�R���X�g���N�^
�����F�Ȃ�
=====================*/
Pause::Pause()
	:
	mpPlayScene(nullptr),
	mpTexture(nullptr),
	mpCursor(nullptr),
	mState(static_cast<int>(SelectState::KEEP)),
	mControlUIDrawFlag(true)
{
	mpTexture = std::make_unique<ObjectTexture>();
	mpCursor = std::make_unique<Cursor>();
}

/*=====================
�f�X�g���N�^
=====================*/
Pause::~Pause()
{
}

/*===============================
����������
�����F�v���C�V�[���̃|�C���^
�Ԃ�l�F�Ȃ�
===============================*/
void Pause::Initialize(PlayScene* pPlayScene, UI* pUI)
{
	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;
	mpUI = pUI;

	auto pResouceManager = ResourceManager::GetInstance();
	auto texture = pResouceManager->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__PAUSE));

	//�摜�̐ݒ�
	mpTexture->SetTexture(texture);
	mpTexture->Initialize();

	//�J�[�\���̏���������
	mpCursor->Initialize(
		static_cast<int>(PlayTexturesResouce::TEXTURE__CURSOR),
		SELECT_CURSOR_INIT_POSITION,
		SELECT_CURSOR_SCALE,
		SELECT_CURSOR_SHIFT);
}

/*=====================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�I���t���O
=====================*/
bool Pause::Update()
{
	//�J�[�\���̈ʒu�ݒ�
	this->MoveCursor();

	//���s����
	switch (this->Execution())
	{
		case SelectState::CONFIG_CONTROL:
		{
			//UI�`���؂�ւ���			
			this->UpdateControlUI();

			return false;
			break;
		}
		case SelectState::KEEP:
		{
			return true;
			break;
		}
		case SelectState::RETRY:
		{
			mpPlayScene->SetRetryFlag(true);
			return true;
			break;
		}
		case SelectState::TO_STAGE_SELECT:
		{
			mpPlayScene->SetClearFlag(true);
			return true;
			break;
		}
		
		case SelectState::NONE:
		{
			return false;
			break;
		}
	}
	return false;
}

/*===============================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===============================*/
void Pause::Draw()
{
	//�摜�̕`��
	mpTexture->Draw();

	//�J�[�\���̕`��
	mpCursor->Draw();

	//����UI�̕����`��
	this->DrawControlUIString();

}

/*=====================
�J�[�\���ړ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================*/
void Pause::MoveCursor()
{
	//�L�[���͂��擾
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//�J�[�\�������
	if (pKey->SelectOver() || pGamePad->ChangeCursorUp())
	{
		//�ő�l�ł͂Ȃ�������
		if (static_cast<SelectState>(mState) > SelectState::CONFIG_CONTROL)
		{
			//�J�[�\�����X�V
			mState--;
			mpCursor->CursorUp(); 
		}
	}
	//�J�[�\��������
	if (pKey->SelectUnder() || pGamePad->ChangeCursorDown())
	{
		//�ŏ��l�ł͂Ȃ�������
		if (static_cast<SelectState>(mState)< SelectState::TO_STAGE_SELECT)
		{
			//�J�[�\�����X�V
			mState++;
			mpCursor->CursorDown();
		}
	}
}

/*==========================
���݂̏�Ԃ����s:private
�����F�Ȃ�
�Ԃ�l�F���݂̏��
===========================*/
Pause::SelectState Pause::Execution()
{
	//�L�[���͂��擾
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//���肪������Ȃ������珈�������Ȃ�
	if ((pKey->Decision() || pGamePad->Decision()))
	{
		return static_cast<SelectState>(mState);
	}	

	return SelectState::NONE;
}

/*==========================
UI�`�揈��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===========================*/
void Pause::UpdateControlUI()
{
	//UI�`���؂�ւ���
	mpUI->ChangeDrawControlUIFlag();

	//���݂̏�Ԃ𒲂ׁA���̃N���X�̊Ǘ��t���O��ݒ肷��
	if (mpUI->GetDrawControlUIFlag())
	{
		mControlUIDrawFlag = true;
	}
	else
	{
		mControlUIDrawFlag = false;
	}
}

/*==========================
����UI�̕����`��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===========================*/
void Pause::DrawControlUIString()
{
	//�F�w��
	DirectX::SimpleMath::Vector4 onColor = DirectX::Colors::White;
	DirectX::SimpleMath::Vector4 offColor = DirectX::Colors::White;

	if (mControlUIDrawFlag)
	{
		onColor = DirectX::Colors::Red;
	}
	else
	{
		offColor = DirectX::Colors::Red;
	}


	Utility::DrawString(L"ON", SELECT_STRING_ON_POS, onColor);
	Utility::DrawString(L"/", SELECT_STRING_SLASH_POS);
	Utility::DrawString(L"OFF", SELECT_STRING_OFF_POS, offColor);

}
