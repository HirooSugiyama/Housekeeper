/*
������@�`��UI
�쐬�ҁF���R
�쐬���F2022/01/30
*/
#include"pch.h"

#include"ControlPanel.h"

//�萔�Q
#include"ControlPanelConstant.h"


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
ControlPanel::ControlPanel()
	:
	mpMove(),
	mpAttack(),
	mpChange(),
	mpPause(),
	mpReStart(),
	mDrawFlag(true)
{
	mpMove = std::make_unique<ObjectSpriteTexture>();
	mpAttack = std::make_unique<ObjectSpriteTexture>();
	mpChange = std::make_unique<ObjectSpriteTexture>();
	mpPause = std::make_unique<ObjectSpriteTexture>();
	mpReStart = std::make_unique<ObjectSpriteTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
ControlPanel::~ControlPanel()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ControlPanel::Initialize()
{
	//���\�[�X�}�l�[�W�����烊�\�[�X���擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__CONTROLSPRITE));

	//����������
	mpMove->Initialize();
	mpAttack->Initialize();
	mpChange->Initialize();
	mpPause->Initialize();
	mpReStart->Initialize();

	//�摜�ݒ菈��
	mpMove->SetTexture(texture);
	mpAttack->SetTexture(texture);
	mpChange->SetTexture(texture);
	mpPause->SetTexture(texture);
	mpReStart->SetTexture(texture);

	//���W�ݒ菈��
	mpMove->SetPosition(ControlPanelConstant::MOVE_POS);
	mpAttack->SetPosition(ControlPanelConstant::ATTACK_POS);
	mpChange->SetPosition(ControlPanelConstant::CHANGE_POS);
	mpPause->SetPosition(ControlPanelConstant::PAUSE_POS);
	mpReStart->SetPosition(ControlPanelConstant::RESTART_POS);

	//���W�ݒ菈��
	mpMove->SetScale(ControlPanelConstant::TEX_SCALE);
	mpAttack->SetScale(ControlPanelConstant::TEX_SCALE);
	mpChange->SetScale(ControlPanelConstant::TEX_SCALE);
	mpPause->SetScale(ControlPanelConstant::TEX_SCALE);
	mpReStart->SetScale(ControlPanelConstant::TEX_SCALE);

	//�摜�؂���ʒu���w��
	mpMove->SetRect(ControlPanelConstant::MOVE_RECT);
	mpAttack->SetRect(ControlPanelConstant::ATTACK_RECT);
	mpChange->SetRect(ControlPanelConstant::CHANGE_RECT);
	mpPause->SetRect(ControlPanelConstant::PAUSE_RECT);
	mpReStart->SetRect(ControlPanelConstant::RESTART_RECT);

}

/*==================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ControlPanel::Draw()
{
	//�`��t���O���~��Ă���ꍇ���������Ȃ�
	if (!mDrawFlag)return;

	//�`�揈��
	mpMove->Draw();
	mpAttack->Draw();
	mpChange->Draw();
	mpPause->Draw();
	mpReStart->Draw();
}

/*===================================
�Q�[���p�b�h�ƃL�[��؂�ւ�
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ControlPanel::ChangeControl()
{
	//�Q�[���p�b�h�g�p�󋵂��擾
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	//�g�p���̏���
	if (pGamePadTracker->GetUseFlag())
	{
		//�摜�؂���ʒu���w��
		RECT rect = ControlPanelConstant::MOVE_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpMove->SetRect(rect);

		rect = ControlPanelConstant::ATTACK_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpAttack->SetRect(rect);

		rect = ControlPanelConstant::CHANGE_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpChange->SetRect(rect);

		rect = ControlPanelConstant::PAUSE_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpPause->SetRect(rect);
		rect = ControlPanelConstant::RESTART_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpReStart->SetRect(rect);
	}
	//���g�p���̏���
	else
	{
		//�摜�؂���ʒu���w��
		mpMove->SetRect(ControlPanelConstant::MOVE_RECT);
		mpAttack->SetRect(ControlPanelConstant::ATTACK_RECT);
		mpChange->SetRect(ControlPanelConstant::CHANGE_RECT);
		mpPause->SetRect(ControlPanelConstant::PAUSE_RECT);
		mpReStart->SetRect(ControlPanelConstant::RESTART_RECT);
	}
}
