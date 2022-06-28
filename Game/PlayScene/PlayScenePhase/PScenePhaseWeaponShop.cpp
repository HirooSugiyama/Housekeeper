/*
����w���t�F�[�Y
�쐬�ҁF���R
�쐬���F2021/09/30
*/

#include"pch.h"
#include"PScenePhaseWeaponShop.h"

//������
#include"../PlayScene.h"

//�������̎擾
#include"../../Money/Money.h"

//�֐������̎g�p
#include"../../UI/UI.h"
#include"../PlaySceneCommon/Weapon/WeaponBase.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/Player/ActionStateAttackEnemy.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"
#include"../PlaySceneCommon/Bullet/BulletType.h"
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"
#include"Game/PlayScene/PlaySceneCommon/Bullet/BulletStateBoomerang.h"

//�w�ʉ摜�̏������W
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACKGROUND_TEXTURE_INIT_POSITION(0.f, 0.f);
//�w�ʉ摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACKGROUND_TEXTURE_SCALE(1.f, 1.f);

//�J�[�\���̍��W
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::CURSOR_INIT_POSITION(20.f, 217.f);
//�J�[�\���̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::CURSOR_SCALE(0.25f, 0.25f);
//�J�[�\���̈ړ���
const float PScenePhaseWeaponShop::CURSOR_SHIFT = 98.f;

//�_�ŉ摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACK_TEX_SCALE(0.3f, 0.3f);
//�_�ŉ摜�̍��W
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACK_TEX_POSITION(0.f, 0.f);

//��_�J�����̍��W
const DirectX::SimpleMath::Vector3 PScenePhaseWeaponShop::PIXED_CAMERA_POSITION(0.0f, 2.0f, 10.0f);

//�e�����̐F
const DirectX::SimpleMath::Vector4 PScenePhaseWeaponShop::STRING_COLOR(0.7f, 0.7f, 0.7f, 1.f);

//�l�i
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_PRICENUM_POSITION(830.f, 505.f);
//�U����
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_ATTACKNUM_POSITION(960.f, 575.f);
//�e��
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_BULLETNUM_POSITION(960.f, 645.f);


//�_�ŉ摜�̏����؂�����W
const RECT PScenePhaseWeaponShop::BACK_TEX_INIT_RECT{ 0,0,595,178 };


/*=====================
�R���X�g���N�^
�����F�Ȃ�
=====================*/
PScenePhaseWeaponShop::PScenePhaseWeaponShop()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mpWeaponManager(nullptr),
	mpBackTexture(nullptr),
	mSelectWeaponNum(1),
	mpShopCursor(nullptr),
	mpBackGroundTexture(nullptr),
	mpRotWeaponSample(nullptr),
	mpFixedPointCamera(nullptr),
	mpTextureBlinking(nullptr),
	mSelectWeaponBulletNum(0),
	mSelectWeaponPrice(0),
	mSelectWeaponAttackNum(0),
	mpWeaponExplanatory(nullptr),
	mDefenceBackFlag(false),
	mpConfirmationScreen(nullptr),
	mConfirmationFlag(false)
{
	mpWeaponManager = std::make_unique<WeaponManager>();
	mpShopCursor = std::make_unique<Cursor>();
	mpBackGroundTexture = std::make_unique<ObjectTexture>();
	mpRotWeaponSample = std::make_unique<RotWeaponSample>();
	mpFixedPointCamera = std::make_unique<FixedPointCamera>();
	mpBackTexture = std::make_unique<ObjectSpriteTexture>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpWeaponExplanatory = std::make_unique<WeaponExplanatory>();
	mpConfirmationScreen = std::make_unique<ConfirmationScreen>();
}

/*=====================
�f�X�g���N�^
=====================*/
PScenePhaseWeaponShop::~PScenePhaseWeaponShop()
{
}

/*=====================
����������
�����F���L��̃|�C���^
�Ԃ�l�F�Ȃ�
=====================*/
void PScenePhaseWeaponShop::Initialize(PlayScene* pPlayScene)
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__WEAPONBACKGROUND));

	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	//�J�[�\���̏���������
	mpShopCursor->Initialize(
		static_cast<int>(PlayTexturesResouce::TEXTURE__CURSOR),
		CURSOR_INIT_POSITION,
		CURSOR_SCALE,
		CURSOR_SHIFT);

	//�摜�ǂݍ��ݏ���
	mpBackGroundTexture->Initialize();
	mpBackTexture->Initialize();

	//�w�i�摜�̏���������
	mpBackGroundTexture->SetTexture(texture);
	mpBackGroundTexture->SetPosition(BACKGROUND_TEXTURE_INIT_POSITION);
	mpBackGroundTexture->SetScale(BACKGROUND_TEXTURE_SCALE);

	//�W�����{���f���̏���������
	mpRotWeaponSample->Initialize();

	//����Ǘ��N���X�̏���������
	mpWeaponManager->Initialize(PlayScenePhaseBase::GetBulletManager());

	//����Ή���������ɐ؂�ւ���
	this->ChangeInfoSelectWeapon();

	//�_�ŉ摜�̉摜�ݒ菈��
	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__BACK));
	mpBackTexture->SetTexture(texture);
	mpBackTexture->SetScale(BACK_TEX_SCALE);
	mpBackTexture->SetPosition(BACK_TEX_POSITION);
	mpBackTexture->SetRect(BACK_TEX_INIT_RECT);

	//�ŏ��̓}�V���K����ݒ肵�Ă���(�ŏ��̍��ڂ̓}�V���K���Œ�)
	//�Ώۂ̃��f����W�����f����
	DirectX::Model* model =
		mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
		WeaponBase::GetWeaponModel()->GetModel();

	mpRotWeaponSample->SetWeaponModel(model);

	//����Ή���������ɐ؂�ւ���
	this->ChangeInfoSelectWeapon();

	//�������̏���������
	mpWeaponExplanatory->Initialize();

	//�m�F��ʂ̏���������
	mpConfirmationScreen->Initialize(static_cast<int>(PlayTexturesResouce::TEXTURE__WEAPONBUYSTRING));
}

/*=====================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================*/
void PScenePhaseWeaponShop::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//���͋@�픻�菈��
	this->ChackControl();

	//�W�����{���f���̍X�V����
	mpRotWeaponSample->Update();

	//�_�ŏ����̍X�V
	mpTextureBlinking->Update();

	//���ԃt���O
	bool timerFlag = true;

	//�m�F��ʂ̍X�V����
	if (mConfirmationFlag)
	{
		timerFlag = mpConfirmationScreen->Update();
	}
	if (timerFlag)
	{
		//����I������
		this->SelectWeapon();
	}
	


	//�h�q�֖߂鏈��
	if (pKey->Back()|| pGamePad->Back())
	{
		auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();

		mDefenceBackFlag = true;
		//���C�v����
		if (pSTI.GetWipe()->GetState())
		{
			pSTI.SetWipeUseFlag(true);
			pSTI.GetWipe()->SetClose();
			return;
		}	
	}
	if (mDefenceBackFlag)
	{
		auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
		//�e��ݒ肷��

		//�h�q�t�F�[�Y��
		mpPlayScene->ChangePhaseToDefence();

		//���Z�b�g�������s��
		mpPlayScene->GetPhase()->Reset();

		//���C�v����
		pSTI.SetWipeUseFlag(true);
		pSTI.GetWipe()->SetOpen();
	}
}

/*==============================
State�ύX�O�̃��Z�b�g����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
================================*/
void PScenePhaseWeaponShop::Reset()
{
	//��_�J�����Ɉړ�
	mpPlayScene->ChangeFixedCamera();

	//�J�����s����擾
	auto& pPVIf = CameraInfoComponent::GetCameraInfoComponentInstance();

	//��_�J�����ɕύX����
	mpFixedPointCamera->SetEyePosition(PIXED_CAMERA_POSITION);			//���W�w��
	pPVIf.SetProjection(mpFixedPointCamera->GetProjectionMatrix());
	pPVIf.SetView(mpFixedPointCamera->GetViewMatrix());

	mDefenceBackFlag = false;

	//�m�F���
	mConfirmationFlag = false;

	//���C�v����
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.SetWipeUseFlag(true);
	pSTI.GetWipe()->SetOpen();
}

/*================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
================================*/
void PScenePhaseWeaponShop::Draw()
{
	//�w�i�̕`��
	mpBackGroundTexture->Draw();

	//�J�[�\���̕`��
	mpShopCursor->Draw(true);

	//�W�����{���f���̕`�揈��
	mpRotWeaponSample->Draw();

	//�������̕`��
	PlayScenePhaseBase::GetUI()->DrawMoneyTexture();


	//�l�i�̕`��
	Utility::DrawString(mSelectWeaponPrice, STRING_PRICENUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_LARGE);

	//�U���͒l�̕`��
	Utility::DrawString(mSelectWeaponAttackNum, STRING_ATTACKNUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_LARGE);

	//�e���̕`��
	Utility::DrawString(mSelectWeaponBulletNum, STRING_BULLETNUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_LARGE);

	//�������̕`��
	mpWeaponExplanatory->Draw();
	 
	if (mpTextureBlinking->GetBlinkingFlag())
	{
		mpBackTexture->Draw();
	}


	//�m�F��ʂ̍X�V����
	if (mConfirmationFlag)
	{
		mpConfirmationScreen->Draw(mpTextureBlinking->GetBlinkingFlag());

	}

}

/*===============================
���͋@�픻�菈��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseWeaponShop::ChackControl()
{
	//�Q�[���p�b�h�g�p�󋵂��擾
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	RECT rect = BACK_TEX_INIT_RECT;

	//�g�p���̏���
	if (pGamePadTracker->GetUseFlag())
	{
		rect.top = BACK_TEX_INIT_RECT.bottom;
		rect.bottom *= Utility::SHIFT_SPRITE_TEXTURE;
		mpBackTexture->SetRect(rect);
	}
	//�p�b�h���g�p���̏���
	else
	{
		mpBackTexture->SetRect(rect);
	}
}

/*===============================
�����I������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseWeaponShop::SelectWeapon()
{
	//�m�F��ʂł͂Ȃ��ꍇ�̂ݑI���������s��
	if (!mConfirmationFlag)
	{
		//�J�[�\����������
		this->ShopCursorDown();

		//�J�[�\�����グ��
		this->ShopCursorUp();
	}

	//����𔃂�
	this->BuyWeapon();
}


/*=================================
�J�[�\����������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseWeaponShop::ShopCursorUp()
{

	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver()|| pGamePad->ChangeCursorUp())
	{
		//�ő�X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
		if (mSelectWeaponNum - 1 != static_cast<int>(eWeaponType::NONE))
		{
			//�摜�����
			mpShopCursor->CursorUp();
			mSelectWeaponNum--;

			//�Ώۂ̃��f����W�����f����
			DirectX::Model* model= 
				mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				WeaponBase::GetWeaponModel()->GetModel();

			mpRotWeaponSample->SetWeaponModel(model);

			//����Ή���������ɐ؂�ւ���
			this->ChangeInfoSelectWeapon();

			//�Љ�̕ύX
			mpWeaponExplanatory->Update(static_cast<eWeaponType>(mSelectWeaponNum));

		}
	}
}

/*=================================
�J�[�\����������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseWeaponShop::ShopCursorDown()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectUnder()|| pGamePad->ChangeCursorDown())
	{
		//�ŏ��X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
		if (mSelectWeaponNum + 1 != static_cast<int>(eWeaponType::NUM))
		{
			//�摜������
			mpShopCursor->CursorDown();
			mSelectWeaponNum++;

			//�Ώۂ̃��f����W�����f����
			DirectX::Model* model =
				mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				WeaponBase::GetWeaponModel()->GetModel();

			mpRotWeaponSample->SetWeaponModel(model);

			//����Ή���������ɐ؂�ւ���
			this->ChangeInfoSelectWeapon();

			//�Љ�̕ύX
			mpWeaponExplanatory->Update(static_cast<eWeaponType>(mSelectWeaponNum));
		}
	}
}


/*========================================
����𔃂�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void PScenePhaseWeaponShop::BuyWeapon()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//��������{�^���������ꂽ��
	if (pKey->Decision()|| pGamePad->Decision())
	{
		//�m�F��ʂłȂ����
		if (!mConfirmationFlag)
		{
			//�m�F��ʕ`��
			mConfirmationFlag = true;

			return;
		}
		//�m�F��ʂ�(Yes)�Ȃ�
		else if (mpConfirmationScreen->GetSelectFlag())
		{
			//����������邩�ǂ����`�F�b�N
			Money& pM = Money::GetMoneyInstance();
			int money = pM.GetMoney();

			//���z�������Ă���
			int weaponprice =
				mpWeaponManager->
				GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				GetWeaponPrice();

			//�������̂ق������������珈��������
			if (!(money >= weaponprice))
			{
				//�m�F��ʕ`��
				mConfirmationFlag = false;
				return;
			}

			//�����������炵��
			pM.ReduceMoney(weaponprice);

			PlayScenePhaseBase::GetUI()->CreateMoneyEffect(weaponprice);

			//�v���C���[�̕����Ԃ�ύX���Ă���
			PlayScenePhaseBase::GetPlayer()->ChangePlayerActionStateStrongWeapon();

			//����������ς���
			PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->ChangeStrongWeapon
			(
				static_cast<eWeaponType>(mSelectWeaponNum)
			);

			//����摜��ύX����
			PlayScenePhaseBase::GetUI()->ChangeActionInfoTexture(ePlayerActionState::STRONG_WEWPON);
			PlayScenePhaseBase::GetUI()->
				ChangeActionInfoTexture(static_cast<eWeaponType>(mSelectWeaponNum));	
		
		}
		//�m�F��ʗp�J�[�\���̃^�C�}�[�����Z�b�g����
		mpConfirmationScreen->Reset();
		//�m�F��ʕ`��
		mConfirmationFlag = false;

	}
}

/*========================================
����Ή���������ɐ؂�ւ���:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void PScenePhaseWeaponShop::ChangeInfoSelectWeapon()
{

	//�Ώۂ̕���̑��e�����擾
	mSelectWeaponBulletNum = mpWeaponManager->
		GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->GetBulletNum();

	//�Ώۂ̕���̋��z���擾
	mSelectWeaponPrice = mpWeaponManager->
		GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->GetWeaponPrice();

	//�Ώۂ̕���̍U���͂��擾
	mSelectWeaponAttackNum = PlayScenePhaseBase::GetBulletManager()->GetBulletType()->
		GetBulletInfomation(static_cast<eWeaponType>(mSelectWeaponNum))->mBulletAttackNum;
}
