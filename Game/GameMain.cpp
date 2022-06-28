/*
ゲームメイン
作成者：杉山
作成日：2021/10/21
*/
#include "pch.h"

#include "DeviceResources.h"
#include "GameMain.h"


#include "Game/TitleScene/TitleScene.h"
#include "Game/StageSelect/StageSelectScene.h"
#include "Game/PlayScene/PlayScene.h"

//各種シーンインターフェース
#include"Game/Component/SceneComponent/PtoRSceneComponent.h"
#include"Game/Component/SceneComponent/StoPSceneComponent.h"


//所持金の取得
#include"Money/Money.h"
#include"Libraries/MyLibraries/Adx2.h"

//ゲームパッドアイコン
//座標
const DirectX::SimpleMath::Vector2 GameMain::GAMEPAD_ICON_POSITION(0.f,0.f);
//拡大率
const DirectX::SimpleMath::Vector2 GameMain::GAMEPAD_ICON_SCALE(0.f,0.f);


/*=========================================
コンストラクタ
引数：なし
=========================================*/
GameMain::GameMain()
	: 
	mNextScene(eGameScene::TITLE),		// 初期シーンの設定
	mpScene(nullptr)
{
}


/*=========================================
デストラクタ
=========================================*/
GameMain::~GameMain()
{
	this->Finalize();

	// サウンドの終了処理
	ADX2::GetInstance().Finalize();
}


/*=========================================
初期化処理
引数：なし
返り値：なし
=========================================*/
void GameMain::Initialize()
{
	// サウンドの初期化
	ADX2::GetInstance().Initialize
	("Resources/Audio/Housekeeper_Sound.acf", "Resources/Audio/CueSheet_0.acb");

	//ワイプ処理
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.GetWipe()->Initialize();
	pSTI.GetFade()->Initialize();


	// シーン作成
	this->CreateScene();

}

/*=========================================
更新
引数：タイマー
返り値：なし
=========================================*/
void GameMain::Update(const DX::StepTimer& timer)
{
	//キーボードの更新処理
	this->KeyboardUpdate();

	//ゲームパッドの更新処理
	this->GamePadUpdate();
	
	//タイマーの更新
	auto& pTM = TimerComponent::GetTimerInstance();
	pTM.SetTimer(timer);

	//ワイプ処理
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	bool flag{ false };
	if (pSTI.GetWipeUseFlag())
	{
		flag = pSTI.GetWipe()->Update(static_cast<float>(pTM.GetTimer().GetElapsedSeconds()));
		if (flag)pSTI.SetWipeUseFlag(false);
	}
	else if (pSTI.GetFadeUseFlag())
	{
		//フェード処理
		flag = pSTI.GetFade()->Update(static_cast<float>(pTM.GetTimer().GetElapsedSeconds()));
		if (flag)pSTI.SetFadeUseFlag(false);
	}
	
	

	//ワイプ中なら処理をしない
	if (pSTI.GetWipeUseFlag())return;

	//フェードイン中なら処理をしない
	if (pSTI.GetFadeUseFlag()&&!pSTI.GetFade()->GetFlagOpen())return;

	// 次のシーンが設定されていたらシーン切り替え
	if (mNextScene != eGameScene::NONE)
	{
		// シーン削除
		DeleteScene();

		//リソースマネージャの内容の削除
		auto pRM = ResourceManager::GetInstance();
		pRM->Finalize();//メモリの解放


	
		// シーン作成
		CreateScene();
	}
	
	// 実態があれば更新
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update();
	}

}


/*=========================================
描画
引数：なし
返り値：なし
=========================================*/
void GameMain::Render()
{
	// 実態があれば描画
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}

	//ワイプ処理
	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.GetWipe()->Draw();
	pSTI.GetFade()->Draw();
}


/*=========================================
終了処理
引数：なし
返り値：なし
=========================================*/
void GameMain::Finalize()
{
	this->DeleteScene();
	//リソース関係の初期設定
	//リソースマネージャに画像を保存する
	auto pRM = ResourceManager::GetInstance();
	//データ初期化
	pRM->Finalize();
}

/*=========================================
シーンの作成:private
引数：なし
返り値：なし
=========================================*/
void GameMain::CreateScene()
{
	// シーンが作成されているときは処理しない
	if (mpScene != nullptr)
	{
		return;
	}

	// 次シーンの作成
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

	// 作成したシーンを初期化
	mpScene->Initialize();

	//次へのScene情報を初期化
	mNextScene = eGameScene::NONE;
}

/*=========================================
シーンの削除：private
引数：なし
返り値：なし
=========================================*/
void GameMain::DeleteScene()
{
	// シーンが作成されていなければ処理しない
	if (mpScene == nullptr)
	{
		return;
	}

	// 現シーンの終了処理
	mpScene->Finalize();

	// 現シーンの削除
	if (mpScene)
	{
		mpScene.reset();
	}
}

/*=========================================
キーボードの更新処理:private
引数：なし
返り値：なし
=========================================*/
void GameMain::KeyboardUpdate()
{
	//トラッカーの取得
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	pKey->KeyUpdate();
}

/*=========================================
ゲームパッドの更新処理:private
引数：なし
返り値：なし
=========================================*/
void GameMain::GamePadUpdate()
{
	//トラッカーの取得
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();
	pGamePad->ButtonUpdate();
}
