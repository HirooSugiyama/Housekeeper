/*
�v���C�V�[��
�쐬�ҁF���R
�쐬���F2021/10/21
*/


//�v���R���p�C���w�b�_�[
#include "pch.h"
//�p����
#include "../GameMain.h"

#include"PlayScene.h"

//�Ԃ�l����̎擾�ŕK�v�Ȃ���
#include"PlaySceneCommon/Administrator/Score.h"
#include"PlaySceneCommon/Administrator/Timer.h"
#include"PlaySceneCommon/Administrator/CelestialSphere.h"




//��񋤗L�Ŏg�p
#include"Game/Component/SceneComponent/PtoRSceneComponent.h"
#include"Game/Component/SceneComponent/StoPSceneComponent.h"

//UI�̕\��
#include"Game/UI/UI.h"

//���z�̎擾
#include"Game/Money/Money.h"

//�G�t�F�N�g�̎擾
#include"Effect/EffectManager.h"
#include"Effect/Effect.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//���C�g���Ƃ炷����
const DirectX::SimpleMath::Vector3 PlayScene::LIGHT_DIRECTION(-1.f, -1.f, -1.f);


/*===================================
�R���X�g���N�^
�����F�Ȃ�
*===================================*/
PlayScene::PlayScene()
	: 
	mpCamera(nullptr),
	mpFixedCamera(nullptr),			
	mpMainCamera(nullptr),
	mpRotCamera(nullptr),
	mpBasicEffect(nullptr),
	mpInputLayout(nullptr),
	mpWallManager(nullptr),
	mpPlayer(nullptr),
	mpEnemyManager(nullptr),
	mpBlockManager(nullptr),
	mpProtecter(nullptr),
	mpAdministrator(nullptr),
	mpGround(nullptr),
	mpGroundObjectManager(nullptr),
	mpGridLineManager(nullptr),
	mpWeaponManager(nullptr),
	mpBulletManager(nullptr),
	mpUI(nullptr),
	mpPSPhase(nullptr),
	mPlayScenePhase(ePlayScenePhase::ROTATION_CAMERA),
	mPhaseCount(0),
	mAllPhaseNum(0),
	mClearFlag(false),
	mRetryFlag(false),
	mStageNumber("none"),
	mBGMID(Utility::EXCEPTION_NUM),
	mPauseFlag(false),
	mpPause(nullptr)
{
	//���\�[�X�֌W�̏����ݒ�
	//���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	auto pRM = ResourceManager::GetInstance();
	//�f�[�^������
	pRM->Finalize();
	//���\�[�X�̓ǂݍ���
	pRM->Load(ReadRange::PLAY_MODELS_RESOUCE);
	pRM->Load(ReadRange::PLAY_TEXTURES_RESOUCE);
	pRM->Load(ReadRange::STAGESELECT_TEXTURES_RESOUCE);
	
	mpFixedCamera = std::make_unique<FixedPointCamera>();
	mpMainCamera = std::make_unique<Camera>();
	mpRotCamera = std::make_unique<RotationCamera>();
	
	
	mpAdministrator = std::make_unique<Administrator>();
	mpWallManager = std::make_unique<WallManager>();
	mpPlayer = std::make_unique<Player>();
	mpBlockManager = std::make_unique<BlockManager>();
	mpGround = std::make_unique<Ground>();
	mpGridLineManager = std::make_unique<GridLineManager>();
	mpWeaponManager = std::make_unique<WeaponManager>();
	
	mpBulletManager = std::make_unique<BulletManager>();
	mpUI = std::make_unique<UI>();
	
	mpPhaseVector.resize(static_cast<int>(ePlayScenePhase::PHASE_MAX_NUM));
	mpPhaseVector[static_cast<int>(ePlayScenePhase::ROTATION_CAMERA)] = std::make_unique<PScenePhaseRotationCamera>();
	mpPhaseVector[static_cast<int>(ePlayScenePhase::COUNTDOWN)] = std::make_unique<PScenePhaseCountDown>();
	mpPhaseVector[static_cast<int>(ePlayScenePhase::DEFENCE)] = std::make_unique<PScenePhaseDefense>();
	mpPhaseVector[static_cast<int>(ePlayScenePhase::WEAPON_SHOP)] = std::make_unique<PScenePhaseWeaponShop>();
	mpPhaseVector[static_cast<int>(ePlayScenePhase::END_ANIMATION)] = std::make_unique<PScenePhaseEndAnimation>();
	mpPhaseVector[static_cast<int>(ePlayScenePhase::RESULT)] = std::make_unique<PScenePhaseResult>();

	mpPause = std::make_unique<Pause>();
	
	//�C���^�[�t�F�[�X����̏�񂪕K�v�ȃI�u�W�F�N�g�̃������m�ۏ���
	this->IntarfaceGetInfomation();
}

/*===================================
�f�X�g���N�^
*===================================*/
PlayScene::~PlayScene()
{
	//�G�t�F�N�g�}�l�[�W���[�̏I������
	auto pEM = EffectManager::GetInstance();
	pEM->Finalize();

	//�Փ˔���̍폜����
	Collider& pC = Collider::GetColliderInstance();
	pC.Destroy();

	this->StopBGM();
}

/*===================================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
*===================================*/
void PlayScene::Initialize()
{
	//�C���X�^���X�̎擾
	const auto pDR = DX::DeviceResources::GetInstance();
	auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();

	// �f�o�C�X�̎擾
	auto device = pDR->GetD3DDevice();

	// �J�����̏����ݒ�
	//�ŏ��͉�]�J����
	this->ChangeRotCamera();

	//�V���O���g������擾(�擾�Ɠ����ɃJ��������l��Ⴂ�ۑ�����)
	pCiIF.SetView(mpCamera->GetViewMatrix());
	pCiIF.SetProjection(mpCamera->GetProjectionMatrix());


	//�x�[�V�b�N�G�t�F�N�g�̍쐬
	mpBasicEffect = std::make_unique<DirectX::BasicEffect>(device);


	//���_�������肷�邽�߂ɕK�v�ȏ��
	mpBasicEffect->SetLightingEnabled(false);		//���C�gOFF
	mpBasicEffect->SetTextureEnabled(true);			//�e�N�X�`��ON
	mpBasicEffect->SetVertexColorEnabled(false);	//���_�J���[OFF


	//���̓��C�A�E�g���쐬���邽�߂ɕK�v�ȏ��
	const void* shaderByteCode;
	size_t byteCodeLength;

	//�g�p���钸�_�V�F�[�_�[���̎擾
	mpBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//���̓��C�A�E�g�̍쐬
	device->CreateInputLayout(
		DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		mpInputLayout.GetAddressOf()
	);


	//�G�t�F�N�g�}�l�[�W���[�̏���������
	auto pEM = EffectManager::GetInstance();
	pEM->Initialize(L"Resources/CSV/Effect.csv");
	//�J�����̃|�C���^��ۑ����Ă���
	pEM->SetCameraPointer(mpCamera);

	//�I�u�W�F�N�g�̏���������
	this->InitializeObject();

	//�|�C���^�̕ۑ�
	for (int i = 0; i < static_cast<int>(ePlayScenePhase::PHASE_MAX_NUM); i++)
	{
		mpPhaseVector[i]->SaveCommonPointer
		(
			mpAdministrator.get(),
			mpBlockManager.get(),
			mpEnemyManager.get(),
			mpGridLineManager.get(),
			mpWeaponManager.get(),
			mpWallManager.get(),
			mpPlayer.get(),
			mpGround.get(),
			mpProtecter.get(),
			mpGroundObjectManager.get(),
			mpBulletManager.get(),
			mpUI.get()
		);
	}

	//PlaySceneState�̏���������
	for (int i = 0; i < static_cast<int>(ePlayScenePhase::PHASE_MAX_NUM); i++)
	{
		mpPhaseVector[i]->Initialize(this);
	}

	this->ChangePhaseToRotationCamera();
	mpPSPhase->Reset();
	//���ŏ��̓J����������
	
	//���y�𗬂�
	this->PlayBGM();

	//�|�[�Y����
	mpPause->Initialize(this,mpUI.get());
}

/*=================================
�X�V
����	�F�^�C�}�[�̃w���p�[�֐�
�߂�l	�F���̃V�[���ԍ�
=================================*/
eGameScene PlayScene::Update()
{
	//�|�[�Y����
	this->PauseUpdate();

	//�|�[�Y���̂ݏ������s��
	bool flag = false;
	if (mPauseFlag)
	{
		flag = mpPause->Update();
		if (flag)
		{
			mPauseFlag = false;
			mpUI->SetUIDrawFlag(true);
		}
		else
		{
			return eGameScene::NONE;
		}
	}
	else
	{
		//���X�^�[�g����
		this->ReStart();

		//���݂̏�Ԃ̍X�V����
		mpPSPhase->Update();
	}
	if (mRetryFlag)
	{
		return eGameScene::PLAY;
	}

	//�G�t�F�N�g�̍X�V����
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Update();

	//UI�̍X�V����
	mpUI->Update();


	//�f�o�b�O����
#ifdef DEBUG_PLAYSCENE
	//�f�o�b�O����
	this->Debug();

#endif

	//�G�����ׂď��ł�����
	if (mpEnemyManager->AllEnemyDeathFlag()&& mPlayScenePhase <= ePlayScenePhase::END_ANIMATION)
	{
		this->ChangePhaseToResult();
		mpPSPhase->Reset();
	}
	//�����t���O����������(���_���_���[�W���󂯂���)
	if (mpProtecter->GetDamageFlag()) 
	{
		this->GetEndAnimation()->SetUseAnim(eUseEndAnim::LOSE);
		this->ChangePhaseToEndAnimation();
		mpPSPhase->Reset();
	}

	//�X�e�[�W�I����ʂ�
	if (mClearFlag)
	{
		//�Ȃ��~�߂�
		this->StopBGM();

		return eGameScene::STAGE_SELECT;
	}

	return eGameScene::NONE;
}

/*==================================
�`��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayScene::Draw()
{
	const auto pDR = DX::DeviceResources::GetInstance();
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	// �f�o�C�X�R���e�L�X�g�̎擾
	auto context = pDR->GetD3DDeviceContext();


	// �G�t�F�N�g�Ƀ��C�g�̌��ʂ�ݒ肷��
	// �[���Ԗڂ̃��C�g
	mpBasicEffect->SetLightEnabled(0, true);
	// �g�U���ˌ�
	mpBasicEffect->SetLightDiffuseColor(0, DirectX::SimpleMath::Vector3::One);
	// ���C�g�̏Ǝ˕���
	mpBasicEffect->SetLightDirection(0, LIGHT_DIRECTION);
	// �G�t�F�N�g�̓K�p
	mpBasicEffect->Apply(context);			


	//�`��J�n
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_FrontToBack,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);
	//�����V���b�v�ȊO�Ȃ�Ε`�悷��
	if (mPlayScenePhase != ePlayScenePhase::WEAPON_SHOP)
	{
		//���ʂ̕`�揈��
		this->DrawCommon();
	}

	//���݂̏�Ԃ̕`�揈��
	mpPSPhase->Draw();

	//FPS�\��
	//this->DEBUGString();

	if (mPauseFlag)
	{
		mpPause->Draw();
		mpUI->SetUIDrawFlag(false);
	}

	//�X�v���C�g�o�b�`�̏I��
	pDxIF.GetSpriteBatch()->End();
}

/*===================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayScene::Finalize()
{
	//�I�u�W�F�N�g�̏I������
	this->FinalizeObject();
}


/*=========================================
���y���~�߂�
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void PlayScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}



/*============================================================
�C���^�[�t�F�[�X��������擾:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
============================================================*/
void PlayScene::IntarfaceGetInfomation()
{

	//���[�h�I����ʂ���̏�񋤗L�Ǘ��N���X�̎擾
	const auto& pStoP = StoPSceneComponent::GetStoPIFInstance();
	//�G�̍ő吔��A�C�e���̍ő吔���擾
	mpAdministrator->LoadCSV(pStoP.GetStageCSV());
	
	//�X�e�[�W�ԍ��̕ۑ�
	mStageNumber = pStoP.GetStageNumber();

	
	//�������̏����ݒ�
	auto& pM = Money::GetMoneyInstance();
	pM.LoadFileSet("Resources/CSV/Money.csv");
	pM.SetMoney(mpAdministrator->GetUsePriceNum());
	
	//�Ƃ̑ϋv�l
	mpProtecter = std::make_unique<Protecter>();
	//�G�̃������m�ۗp�ő吔
	mpEnemyManager = std::make_unique<EnemyManager>();
	
	//�t�F�[�Y��
	mAllPhaseNum = mpAdministrator->GetPhaseNum();//�t�F�[�Y����ۑ�
	
	//�G�Ǘ��N���X�Ƀt�F�[�Y����ۑ�
	mpEnemyManager->SetMaxPhaseNum(mAllPhaseNum);
	
	//�ǂݍ��ޓG���t�@�C���̎w��
	mpEnemyManager->SetLoadEnemyFileName(mpEnemyManager->
						CreateLoadEnemyFileName(mStageNumber));
	
	//�ǂݍ��ޒn�`���t�@�C���̎w��
	//�ȗ����p�ϐ��̐錾
	std::string filename="none";
	filename=this->CreateLoadGroundObjectFileName(mStageNumber);

	//�n�`����ǂݍ���
	mpGroundObjectManager = std::make_unique<GroundObjectManager>(filename);

	//UI�֏������L
	mpUI->SetTimerPointer(mpAdministrator->DirectAcceserTimer());
	mpUI->SetProtecterPointer(mpProtecter.get());
	mpUI->SetPhaseCountPointer(&mPhaseCount);
	mpUI->SetPhase(&mPlayScenePhase);
	mpUI->SetPlayerPointer(mpPlayer.get());
	mpUI->SetMaxPhaseNum(mAllPhaseNum);
}
/*============================================================
�I�u�W�F�N�g�̏�����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
============================================================*/
void PlayScene::InitializeObject()
{

	//���ʏ����̃I�u�W�F�N�g�̏������������s���B(Player�̂݃|�C���^�̉e���ŕʏꏊ�ŏ�����)

	//�G�Ǘ��N���X�̏�����
	mpEnemyManager->Initialize(mpCamera, mpAdministrator.get(),mpPlayer.get());
	
	//�e�Ǘ��N���X�̏���������
	mpBlockManager->Initialize(mpEnemyManager.get());
	
	//�Ƃ̏���������
	mpProtecter->Initialize();
	
	//�ǊǗ��N���X�̏���������
	mpWallManager->Initialize();

	//�n��N���X�̏���������
	mpGround->Initialize();
	
	//�Ǘ��N���X�̏���������
	mpAdministrator->Initialize();
	
	//UI�Ǘ��N���X�̏���������
	mpUI->Initialize();

	//�n��I�u�W�F�N�g�Ǘ��N���X�̏���������
	mpGroundObjectManager->Initialize();

	//�O���b�h���Ǘ��N���X�̏���������
	mpGridLineManager->Initialize();

	//����Ǘ��N���X�̏���������
	mpWeaponManager->Initialize(mpBulletManager.get());

	//�e�Ǘ��N���X�̏���������
	mpBulletManager->Initialize(mpCamera,mpPlayer.get(),mpEnemyManager.get());

}

/*============================================================
���ʂ̕`�揈��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
============================================================*/
void PlayScene::DrawCommon()
{
	//���ʏ����̕`��
	//�V���̕`��
	mpAdministrator->DirectAcceserCelestialSphere()->Draw();

	//�n�ʂ̕`��
	mpGround->Draw();

	//�u���b�N�̕`��
	mpBlockManager->Draw();

	//�G�̕`��
	mpEnemyManager->Draw();

	//�O���b�h���̕`��
	mpGridLineManager->Draw();

	//���̕`��
	mpWallManager->Draw();

	//�v���C���[�̕`��
	mpPlayer->Draw();

	//�Ƃ̕`��
	mpProtecter->Draw();

	//�n��I�u�W�F�N�g�̕`��
	mpGroundObjectManager->Draw();

	//�e�Ǘ��N���X�̕`�揈��
	mpBulletManager->Draw();
}

/*============================================================
�I�u�W�F�N�g�̏I������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
============================================================*/
void PlayScene::FinalizeObject()
{
	//�v���C���[�̏I������
	mpPlayer->Finalize();
	//�u���b�N�Ǘ��N���X�̏���������
	mpBlockManager->Finalize();
	//�G�Ǘ��N���X�̏���������
	mpEnemyManager->Finalize();
}

/*========================================
���y�𗬂�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void PlayScene::PlayBGM()
{
	//BGM�̏���������
	mBGMID=ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_PLAY);
}

/*=================================================================
�|�[�Y����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================================================*/
void PlayScene::PauseUpdate()
{
	//�|�[�Y����
	KeyTracker* pK = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();
	if (pK->Pause()|| pGamePadTracker->Pause())
	{
		//���݂��|�[�Y��ԂȂ��
		if (!mPauseFlag)
		{
			mPauseFlag = true;

			//UI���`��ɂ���
			mpUI->SetUIDrawFlag(false);
		}
	}

}

/*=================================================================
���X�^�[�g:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================================================*/
void PlayScene::ReStart()
{
	//�|�[�Y����
	KeyTracker* pK = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();
	if (pK->ReStart()||pGamePadTracker->ReStart())
	{
		mRetryFlag = true;
	}
}

/*=================================================================
�ǂݍ��ޒn�`�I�u�W�F�N�g���Ǘ�����CSV�t�@�C�����w�肷��֐�:private
�����F�X�e�[�W�ԍ�
�Ԃ�l�F�t�@�C����
=================================================================*/
std::string PlayScene::CreateLoadGroundObjectFileName(std::string stagenum)
{
	std::string filetop = "Resources/CSV/GroundObject",
		filebottom = ".csv",
		filename = "none";

	filename = filetop + stagenum + filebottom;

	return filename;
}


/*==================================
FPS�`��Fprivate
�����悯���376�s�ڕt�߂̌Ăяo����
���Ă݂Ă��������B
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PlayScene::DEBUGString()
{
	const auto& pTI = TimerComponent::GetTimerInstance();
	//FPS�`��
	Utility::DrawString
	(
		pTI.GetTimer().GetFramesPerSecond(),
		DirectX::SimpleMath::Vector2(500.f, 0.f),
		DirectX::Colors::White,
		Utility::STRING_SIZE_LARGE
	);
}
