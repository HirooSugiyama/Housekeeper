/*
���[�U�[�C���^�[�t�F�[�X
(�w�肳�ꂽ�Ƃ���Ɏw�肳�ꂽ���̂�`�悷��N���X)
�쐬�ҁF���R
�쐬���F2021/06/23
*/

#include"pch.h"
#include"UI.h"

//�|�C���^�̕ۑ��p
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"
#include"../PlayScene/PlaySceneCommon/Protecter.h"


//�G���`��ʒu
const DirectX::SimpleMath::Vector2 UI::STRING_ENEMY_NUM_POSITION(20.f, 80.f);

//�����������G�t�F�N�g�̈ʒu
const DirectX::SimpleMath::Vector2 UI::MONEY_EFFECT_POSITION(1000.f,100.f);

/*==============
�R���X�g���N�^
�����F�Ȃ�
==============*/
UI::UI()
	:
	mpTimeOfDay(),
	mpMoneyTexture(),
	mpPhaseCursorManager(),
	mpRedAssert(),
	mpPlayerActionInfo(),
	mpDecreaseMoney(),
	mpScoreRender(),
	mpDefeatEnemyRender(),
	mpTimer(),
	mpProtecter(),
	mpPlayer(),
	mpPhaseCountNum(),
	mpPhase(),
	mInitHP(),
	mMaxPhaseNum(),
	mScoreNum(),
	mAllEnemyNum(),
	mRemainingEnemyNum(),
	mUIDrawFlag(true),
	mpControlPanel(nullptr)
{
	//���I�m��
	mpTimeOfDay = std::make_unique<TimeOfDay>();
	mpMoneyTexture = std::make_unique<MoneyTexture>();
	mpPhaseCursorManager = std::make_unique<PhaseCursorManager>();
	mpRedAssert = std::make_unique<RedAssert>();
	mpPlayerActionInfo = std::make_unique<PlayerActionInfo>();
	mpDecreaseMoney = std::make_unique<FloatNumber2D>();
	mpScoreRender = std::make_unique<ScoreRender>();
	mpDefeatEnemyRender = std::make_unique<DefeatEnemyRender>();
	mpControlPanel = std::make_unique<ControlPanel>();

}
/*==============
�f�X�g���N�^
==============*/	
UI::~UI()
{
}


/*========================
������
�����F�J�����̃|�C���^
�Ԃ�l�F�Ȃ�
==========================*/
void UI::Initialize()
{
	//�t�F�[�Y�֌W�̉摜�̏����ݒ�
	mpTimeOfDay->Initialize(mpTimer, mMaxPhaseNum);

	//�������̉��n�摜�̏���������
	mpMoneyTexture->Initialize();

	//�t�F�[�Y�̃J�[�\���̏���������
	mpPhaseCursorManager->Initialize(mMaxPhaseNum);

	//�J�[�\���̍��W��ݒ肷��
	mpPhaseCursorManager->SetDrawPosition
	(
		mpTimeOfDay->GetIconStartPosition(),
		mpTimeOfDay->GetIconDistancePosition()
	);

	//�댯�M���̏���������
	mpRedAssert->Initialize();

	//�v���C���[�̌��݂̏�Ԃ̏���������
	mpPlayerActionInfo->Initialize();

	//�����������G�t�F�N�g�̃t�H���g���w��
	mpDecreaseMoney->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWDAMAGESTRING));
	mpDecreaseMoney->Initialize();

	//�X�R�A����̕`��N���X�̏���������
	mpScoreRender->Initialize();

	//�c��G���̏���������
	mpDefeatEnemyRender->Initialize();

	//������@�`��̏���������
	mpControlPanel->Initialize();
}

/*==============
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============*/
void UI::Update()
{
	//���݂�Phase���h�q�t�F�[�Y�̏ꍇ
	if (*mpPhase == ePlayScenePhase::DEFENCE)
	{
		//�t�F�[�Y�֌W�̉摜�̍X�V����
		mpTimeOfDay->Update();

		//�댯�M���̍X�V����
		mpRedAssert->Update();

		//�����������G�t�F�N�g�̍X�V����
		mpDecreaseMoney->Update();
	}
	//���݂�Phase���V���b�v�t�F�[�Y�̏ꍇ
	if (*mpPhase == ePlayScenePhase::WEAPON_SHOP)
	{
		//�����������G�t�F�N�g�̍X�V����
		mpDecreaseMoney->Update();
	}

	//�Q�[���p�b�h���h�������ۂ̏���
	mpControlPanel->ChangeControl();

}

/*==============
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============*/
void UI::Draw()
{
	//�t���O������Ă���ꍇ�͕`�悵�Ȃ�
	if (!mUIDrawFlag)return;

	//�v���C���[�̌��݂̏�Ԃ̕`�揈��
	mpPlayerActionInfo->Draw();
	
	//�댯�M���̕`�揈��
	mpRedAssert->Draw();
	
	//�t�F�[�Y�֌W�̉摜�̕`��
	mpTimeOfDay->Draw();
	
	//�t�F�[�Y�̃J�[�\���̕`�揈��
	mpPhaseCursorManager->Draw();
	
	//�������֌W�̕`��
	this->DrawMoneyTexture();
	
	//�X�R�A�̕`��
	mpScoreRender->Draw(mScoreNum);
	
	//�c��̓G�̐��̕`��
	mpDefeatEnemyRender->Draw(mRemainingEnemyNum, mAllEnemyNum);

	//������@�`��̕`��
	mpControlPanel->Draw();
}

/*============
�|�C���^�̕ۑ�
�Ԃ�l�F�Ȃ�
==============*/
//�����F�^�C�}�[�̃|�C���^
void UI::SetTimerPointer(Timer* pTimer)
{
	mpTimer = pTimer;
}

//�����F�v���C���[�̃|�C���^
void UI::SetPlayerPointer(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//�����F���_�̃|�C���^
void UI::SetProtecterPointer(Protecter* pProtecter)
{
	mpProtecter = pProtecter;
}

//�����F�t�F�[�Y�J�E���g���̃|�C���^
void UI::SetPhaseCountPointer(int* pPhaseCount)
{
	mpPhaseCountNum = pPhaseCount;
}

//�����F���݂̃t�F�[�Y�̃|�C���^
void UI::SetPhase(ePlayScenePhase* phase)
{
	mpPhase = phase;
}

//�����F����HP
void UI::SetInitHP(const int& pHP)
{
	mInitHP = pHP;
}

//�����F�ő�Phase��
void UI::SetMaxPhaseNum(const int& phasenum)
{
	mMaxPhaseNum = phasenum;
}

//�����F�X�R�A�l
void UI::SetScoreNum(const int& phasenum)
{
	mScoreNum = phasenum;
}
//�����F�S�Ă̓G�̐�
void UI::SetAllEnemyNum(const int& phasenum)
{
	mAllEnemyNum = phasenum;
}
//�����F�|�����G�̐�
void UI::SetRemainingEnemyNum(const int& phasenum)
{
	mRemainingEnemyNum = phasenum;
}


/*==========================
�댯�M���𑀍삷��֐�
�����F�댯�M���t���O
�Ԃ�l�F�Ȃ�
==========================*/
void UI::RedAssertControl(const bool& flag)
{
	mpRedAssert->SetPassFlag(flag);
}

/*========================
�`�悷��摜��ς���֐�
�Ԃ�l�F�Ȃ�
==========================*/
//�����F�v���C���[�̍s�����State
void UI::ChangeActionInfoTexture(const ePlayerActionState & state)
{
	mpPlayerActionInfo->SetPlayerActionState(state);
}
//�����F�����
void UI::ChangeActionInfoTexture(const eWeaponType& type)
{
	mpPlayerActionInfo->SetPlayerWeaponType(type);
}

/*==============================
���݂̕���̒e�����擾����֐�
�����F�e�̒e��
�Ԃ�l�F�Ȃ�
================================*/
void UI::SetActionInfoStrongBulletNum(const int& num)
{
	mpPlayerActionInfo->StrongWeaponBulletNum(num);
}

/*==============================
��������`�悷��֐�
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
================================*/
void UI::DrawMoneyTexture()
{
	//�������̕`��
	mpMoneyTexture->Draw();

	//�����������G�t�F�N�g�̕`��
	mpDecreaseMoney->Draw();
}

/*============================================
�����������G�t�F�N�g���쐬����
�����F�����z
�Ԃ�l�F�Ȃ�
==============================================*/
void UI::CreateMoneyEffect(const int& moneynum)
{
	mpDecreaseMoney->Reset();

	mpDecreaseMoney->Create(moneynum, MONEY_EFFECT_POSITION);
}

/*============================================
�����������G�t�F�N�g���쐬����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==============================================*/
void UI::ChangeDrawControlUIFlag()
{
	//��������ON�Ȃ�
	if (mpControlPanel->GetDrawFlag())
	{
		//OFF�ɂ���
		mpControlPanel->SetDrawFlag(false);
	}
	else
	{
		//ON�ɂ���
		mpControlPanel->SetDrawFlag(true);
	}
}
