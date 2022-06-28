/*
プレイシーン
作成者：杉山
作成日：2021/10/21
*/


//プリコンパイルヘッダー
#include "pch.h"
//継承元
#include "../GameMain.h"

#include"PlayScene.h"

//返り値からの取得で必要なもの
#include"PlaySceneCommon/Administrator/Score.h"
#include"PlaySceneCommon/Administrator/Timer.h"
#include"PlaySceneCommon/Administrator/CelestialSphere.h"




//情報共有で使用
#include"Game/Component/SceneComponent/PtoRSceneComponent.h"
#include"Game/Component/SceneComponent/StoPSceneComponent.h"

//UIの表示
#include"Game/UI/UI.h"

//金額の取得
#include"Game/Money/Money.h"

//エフェクトの取得
#include"Effect/EffectManager.h"
#include"Effect/Effect.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//ライトが照らす方向
const DirectX::SimpleMath::Vector3 PlayScene::LIGHT_DIRECTION(-1.f, -1.f, -1.f);


/*===================================
コンストラクタ
引数：なし
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
	//リソース関係の初期設定
	//リソースマネージャに画像を保存する
	auto pRM = ResourceManager::GetInstance();
	//データ初期化
	pRM->Finalize();
	//リソースの読み込み
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
	
	//インターフェースからの情報が必要なオブジェクトのメモリ確保処理
	this->IntarfaceGetInfomation();
}

/*===================================
デストラクタ
*===================================*/
PlayScene::~PlayScene()
{
	//エフェクトマネージャーの終了処理
	auto pEM = EffectManager::GetInstance();
	pEM->Finalize();

	//衝突判定の削除処理
	Collider& pC = Collider::GetColliderInstance();
	pC.Destroy();

	this->StopBGM();
}

/*===================================
初期化
引数：なし
返り値：なし
*===================================*/
void PlayScene::Initialize()
{
	//インスタンスの取得
	const auto pDR = DX::DeviceResources::GetInstance();
	auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();

	// デバイスの取得
	auto device = pDR->GetD3DDevice();

	// カメラの初期設定
	//最初は回転カメラ
	this->ChangeRotCamera();

	//シングルトンから取得(取得と同時にカメラから値を貰い保存する)
	pCiIF.SetView(mpCamera->GetViewMatrix());
	pCiIF.SetProjection(mpCamera->GetProjectionMatrix());


	//ベーシックエフェクトの作成
	mpBasicEffect = std::make_unique<DirectX::BasicEffect>(device);


	//頂点情報を決定するために必要な情報
	mpBasicEffect->SetLightingEnabled(false);		//ライトOFF
	mpBasicEffect->SetTextureEnabled(true);			//テクスチャON
	mpBasicEffect->SetVertexColorEnabled(false);	//頂点カラーOFF


	//入力レイアウトを作成するために必要な情報
	const void* shaderByteCode;
	size_t byteCodeLength;

	//使用する頂点シェーダー情報の取得
	mpBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//入力レイアウトの作成
	device->CreateInputLayout(
		DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		mpInputLayout.GetAddressOf()
	);


	//エフェクトマネージャーの初期化処理
	auto pEM = EffectManager::GetInstance();
	pEM->Initialize(L"Resources/CSV/Effect.csv");
	//カメラのポインタを保存しておく
	pEM->SetCameraPointer(mpCamera);

	//オブジェクトの初期化処理
	this->InitializeObject();

	//ポインタの保存
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

	//PlaySceneStateの初期化処理
	for (int i = 0; i < static_cast<int>(ePlayScenePhase::PHASE_MAX_NUM); i++)
	{
		mpPhaseVector[i]->Initialize(this);
	}

	this->ChangePhaseToRotationCamera();
	mpPSPhase->Reset();
	//※最初はカメラ旋回状態
	
	//音楽を流す
	this->PlayBGM();

	//ポーズ処理
	mpPause->Initialize(this,mpUI.get());
}

/*=================================
更新
引数	：タイマーのヘルパー関数
戻り値	：次のシーン番号
=================================*/
eGameScene PlayScene::Update()
{
	//ポーズ処理
	this->PauseUpdate();

	//ポーズ中のみ処理を行う
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
		//リスタート処理
		this->ReStart();

		//現在の状態の更新処理
		mpPSPhase->Update();
	}
	if (mRetryFlag)
	{
		return eGameScene::PLAY;
	}

	//エフェクトの更新処理
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Update();

	//UIの更新処理
	mpUI->Update();


	//デバッグ処理
#ifdef DEBUG_PLAYSCENE
	//デバッグ処理
	this->Debug();

#endif

	//敵がすべて消滅したら
	if (mpEnemyManager->AllEnemyDeathFlag()&& mPlayScenePhase <= ePlayScenePhase::END_ANIMATION)
	{
		this->ChangePhaseToResult();
		mpPSPhase->Reset();
	}
	//負けフラグが立ったら(拠点がダメージを受けたら)
	if (mpProtecter->GetDamageFlag()) 
	{
		this->GetEndAnimation()->SetUseAnim(eUseEndAnim::LOSE);
		this->ChangePhaseToEndAnimation();
		mpPSPhase->Reset();
	}

	//ステージ選択画面へ
	if (mClearFlag)
	{
		//曲を止める
		this->StopBGM();

		return eGameScene::STAGE_SELECT;
	}

	return eGameScene::NONE;
}

/*==================================
描画
引数：なし
返り値：なし
===================================*/
void PlayScene::Draw()
{
	const auto pDR = DX::DeviceResources::GetInstance();
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	// デバイスコンテキストの取得
	auto context = pDR->GetD3DDeviceContext();


	// エフェクトにライトの効果を設定する
	// ゼロ番目のライト
	mpBasicEffect->SetLightEnabled(0, true);
	// 拡散反射光
	mpBasicEffect->SetLightDiffuseColor(0, DirectX::SimpleMath::Vector3::One);
	// ライトの照射方向
	mpBasicEffect->SetLightDirection(0, LIGHT_DIRECTION);
	// エフェクトの適用
	mpBasicEffect->Apply(context);			


	//描画開始
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_FrontToBack,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);
	//もしショップ以外ならば描画する
	if (mPlayScenePhase != ePlayScenePhase::WEAPON_SHOP)
	{
		//共通の描画処理
		this->DrawCommon();
	}

	//現在の状態の描画処理
	mpPSPhase->Draw();

	//FPS表示
	//this->DEBUGString();

	if (mPauseFlag)
	{
		mpPause->Draw();
		mpUI->SetUIDrawFlag(false);
	}

	//スプライトバッチの終了
	pDxIF.GetSpriteBatch()->End();
}

/*===================================
終了処理
引数：なし
返り値：なし
===================================*/
void PlayScene::Finalize()
{
	//オブジェクトの終了処理
	this->FinalizeObject();
}


/*=========================================
音楽を止める
引数：なし
返り値：なし
=========================================*/
void PlayScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}



/*============================================================
インターフェースから情報を取得:private
引数：なし
返り値：なし
============================================================*/
void PlayScene::IntarfaceGetInfomation()
{

	//モード選択画面からの情報共有管理クラスの取得
	const auto& pStoP = StoPSceneComponent::GetStoPIFInstance();
	//敵の最大数やアイテムの最大数を取得
	mpAdministrator->LoadCSV(pStoP.GetStageCSV());
	
	//ステージ番号の保存
	mStageNumber = pStoP.GetStageNumber();

	
	//所持金の初期設定
	auto& pM = Money::GetMoneyInstance();
	pM.LoadFileSet("Resources/CSV/Money.csv");
	pM.SetMoney(mpAdministrator->GetUsePriceNum());
	
	//家の耐久値
	mpProtecter = std::make_unique<Protecter>();
	//敵のメモリ確保用最大数
	mpEnemyManager = std::make_unique<EnemyManager>();
	
	//フェーズ数
	mAllPhaseNum = mpAdministrator->GetPhaseNum();//フェーズ数を保存
	
	//敵管理クラスにフェーズ数を保存
	mpEnemyManager->SetMaxPhaseNum(mAllPhaseNum);
	
	//読み込む敵情報ファイルの指定
	mpEnemyManager->SetLoadEnemyFileName(mpEnemyManager->
						CreateLoadEnemyFileName(mStageNumber));
	
	//読み込む地形情報ファイルの指定
	//簡略化用変数の宣言
	std::string filename="none";
	filename=this->CreateLoadGroundObjectFileName(mStageNumber);

	//地形情報を読み込む
	mpGroundObjectManager = std::make_unique<GroundObjectManager>(filename);

	//UIへ情報を共有
	mpUI->SetTimerPointer(mpAdministrator->DirectAcceserTimer());
	mpUI->SetProtecterPointer(mpProtecter.get());
	mpUI->SetPhaseCountPointer(&mPhaseCount);
	mpUI->SetPhase(&mPlayScenePhase);
	mpUI->SetPlayerPointer(mpPlayer.get());
	mpUI->SetMaxPhaseNum(mAllPhaseNum);
}
/*============================================================
オブジェクトの初期化:private
引数：なし
返り値：なし
============================================================*/
void PlayScene::InitializeObject()
{

	//共通処理のオブジェクトの初期化処理を行う。(Playerのみポインタの影響で別場所で初期化)

	//敵管理クラスの初期化
	mpEnemyManager->Initialize(mpCamera, mpAdministrator.get(),mpPlayer.get());
	
	//弾管理クラスの初期化処理
	mpBlockManager->Initialize(mpEnemyManager.get());
	
	//家の初期化処理
	mpProtecter->Initialize();
	
	//壁管理クラスの初期化処理
	mpWallManager->Initialize();

	//地上クラスの初期化処理
	mpGround->Initialize();
	
	//管理クラスの初期化処理
	mpAdministrator->Initialize();
	
	//UI管理クラスの初期化処理
	mpUI->Initialize();

	//地上オブジェクト管理クラスの初期化処理
	mpGroundObjectManager->Initialize();

	//グリッド線管理クラスの初期化処理
	mpGridLineManager->Initialize();

	//武器管理クラスの初期化処理
	mpWeaponManager->Initialize(mpBulletManager.get());

	//弾管理クラスの初期化処理
	mpBulletManager->Initialize(mpCamera,mpPlayer.get(),mpEnemyManager.get());

}

/*============================================================
共通の描画処理:private
引数：なし
返り値：なし
============================================================*/
void PlayScene::DrawCommon()
{
	//共通処理の描画
	//天球の描画
	mpAdministrator->DirectAcceserCelestialSphere()->Draw();

	//地面の描画
	mpGround->Draw();

	//ブロックの描画
	mpBlockManager->Draw();

	//敵の描画
	mpEnemyManager->Draw();

	//グリッド線の描画
	mpGridLineManager->Draw();

	//塀の描画
	mpWallManager->Draw();

	//プレイヤーの描画
	mpPlayer->Draw();

	//家の描画
	mpProtecter->Draw();

	//地上オブジェクトの描画
	mpGroundObjectManager->Draw();

	//弾管理クラスの描画処理
	mpBulletManager->Draw();
}

/*============================================================
オブジェクトの終了処理:private
引数：なし
返り値：なし
============================================================*/
void PlayScene::FinalizeObject()
{
	//プレイヤーの終了処理
	mpPlayer->Finalize();
	//ブロック管理クラスの初期化処理
	mpBlockManager->Finalize();
	//敵管理クラスの初期化処理
	mpEnemyManager->Finalize();
}

/*========================================
音楽を流す:private
引数：なし
返り値：なし
=========================================*/
void PlayScene::PlayBGM()
{
	//BGMの初期化処理
	mBGMID=ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_PLAY);
}

/*=================================================================
ポーズ処理:private
引数：なし
返り値：なし
=================================================================*/
void PlayScene::PauseUpdate()
{
	//ポーズ処理
	KeyTracker* pK = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();
	if (pK->Pause()|| pGamePadTracker->Pause())
	{
		//現在がポーズ状態ならば
		if (!mPauseFlag)
		{
			mPauseFlag = true;

			//UIを非描画にする
			mpUI->SetUIDrawFlag(false);
		}
	}

}

/*=================================================================
リスタート:private
引数：なし
返り値：なし
=================================================================*/
void PlayScene::ReStart()
{
	//ポーズ処理
	KeyTracker* pK = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();
	if (pK->ReStart()||pGamePadTracker->ReStart())
	{
		mRetryFlag = true;
	}
}

/*=================================================================
読み込む地形オブジェクトを管理するCSVファイルを指定する関数:private
引数：ステージ番号
返り値：ファイル名
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
FPS描画：private
もしよければ376行目付近の呼び出しを
つけてみてください。
引数：なし
返り値：なし
===================================*/
void PlayScene::DEBUGString()
{
	const auto& pTI = TimerComponent::GetTimerInstance();
	//FPS描画
	Utility::DrawString
	(
		pTI.GetTimer().GetFramesPerSecond(),
		DirectX::SimpleMath::Vector2(500.f, 0.f),
		DirectX::Colors::White,
		Utility::STRING_SIZE_LARGE
	);
}
