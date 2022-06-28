/*
カメラ旋回フェーズ
作成者：杉山
作成日：2021/10/11
*/

#include"pch.h"
#include"PScenePhaseRotationCamera.h"

//所持元
#include"../PlayScene.h"

//関数内部の使用
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../../Common/ObjectTexture.h"

//エフェクトの描画で使用
#include"../Effect/EffectManager.h"


//カウントダウン時間
const int PScenePhaseRotationCamera::COUNTDOWN_MAX_NUM = 20;

//スキップボタンの座標
const DirectX::SimpleMath::Vector2 PScenePhaseRotationCamera::SKIPBOTTON_POSITION(0.f,0.f);

const DirectX::SimpleMath::Vector2 PScenePhaseRotationCamera::SKIPBOTTON_SCALE(0.15f,0.15f);

//スキップボタンの初期切り取り座標
const RECT PScenePhaseRotationCamera::SKIP_BUTTON_INIT_RECT{ 0,0,1202,352 };

/*=====================
コンストラクタ
引数：なし
=====================*/
PScenePhaseRotationCamera::PScenePhaseRotationCamera()
	:
	mpPlayScene(nullptr),
	mpCountDownTimer(nullptr),
	mpRotationCamera(nullptr),
	mpSkipButton(nullptr),
	mpSkipButtonBlinking(nullptr),
	mState(eRotationState::ROTATION)
{
	mpCountDownTimer = std::make_unique<Timer>();
	mpRotationCamera = std::make_unique<RotationCamera>();
	mpSkipButton = std::make_unique<ObjectSpriteTexture>();
	mpSkipButtonBlinking = std::make_unique<Blinking>();
}

/*=====================
デストラクタ
=====================*/
PScenePhaseRotationCamera::~PScenePhaseRotationCamera()
{
}

/*=====================
初期化処理
引数：所有先のポインタ
返り値：なし
=====================*/
void PScenePhaseRotationCamera::Initialize(PlayScene* pPlayScene)
{
	//リソースの取得
	ResourceManager *pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SKIP));

	mpSkipButton->SetTexture(texture);
	mpSkipButton->Initialize();
	mpSkipButton->SetPosition(SKIPBOTTON_POSITION);
	mpSkipButton->SetScale(SKIPBOTTON_SCALE);
	mpSkipButton->SetRect(SKIP_BUTTON_INIT_RECT);


	//ポインタの保存
	mpPlayScene = pPlayScene;

	//カウントダウン最大時間を設定する
	mpCountDownTimer->SetMaxTime(COUNTDOWN_MAX_NUM);

	//シングルトンへ取得(取得と同時にカメラから値を貰い保存する)
	auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();
	pCiIF.SetView(mpRotationCamera->GetViewMatrix());
	pCiIF.SetProjection(mpRotationCamera->GetProjectionMatrix());

	auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
	pSTI.SetFadeUseFlag(true);
	pSTI.GetFade()->SetOpen();
}

/*=====================
更新処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseRotationCamera::Update()
{
	//点滅処理の更新
	mpSkipButtonBlinking->Update();

	//入力機器判定処理処理
	this->ChackControl();

	//スキップ処理
	bool skipFlag = this->Skip();

	bool timerFlag = false;

	switch (mState)
	{
		case eRotationState::ROTATION:
		{
			//時間判定用変数
			//timerFlag = mpCountDownTimer->ManualUpdate();
			timerFlag = mpCountDownTimer->Update();

			//カメラの更新処理
			mpRotationCamera->Update();
			break;
		}
		case eRotationState::FREE:
		{
			mpRotationCamera->Move();
			break;
		}
	}

	//もしスキップされたら
	if (skipFlag)
	{
		//次のStateへ
		mpPlayScene->ChangePhaseToCountDown();	//カウントダウン状態へ
		mpPlayScene->GetPhase()->Reset();
	}


	//もしカウントダウンが終わったら
	if (timerFlag)
	{
		DirectX::SimpleMath::Vector3 playerpos =
			PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();

		mpRotationCamera->Reset(playerpos);
		mState = eRotationState::FREE;
	}
}

/*====================
描画処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseRotationCamera::Draw()
{
	//エフェクトの描画処理
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();

	if (mpSkipButtonBlinking->GetBlinkingFlag())
	{
		mpSkipButton->Draw();
	}
	
}

/*=================================
リセット処理
引数：なし
返り値：なし
=================================*/
void PScenePhaseRotationCamera::Reset()
{
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->SetCameraPointer(mpRotationCamera.get());
}

/*=================================
入力機器判定処理:private
引数：なし
返り値：なし
=================================*/
void PScenePhaseRotationCamera::ChackControl()
{
	//ゲームパッド使用状況を取得
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	RECT rect = SKIP_BUTTON_INIT_RECT;

	//使用中の処理
	if (pGamePadTracker->GetUseFlag())
	{
		rect.top = SKIP_BUTTON_INIT_RECT.bottom;
		rect.bottom *= Utility::SHIFT_SPRITE_TEXTURE;
		mpSkipButton->SetRect(rect);
	}
	//パッド未使用時の処理
	else
	{
		mpSkipButton->SetRect(rect);
	}
}

/*=================================
スキップ処理:private
引数：なし
返り値：スキップするかしないか
=================================*/
bool PScenePhaseRotationCamera::Skip()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//もしSkipが押されたら
	if (pKey->Skip(mpPlayScene->GetPauseFlag())|| pGamePad->Skip())
	{
		//次の状態へ
		return true;
	}

	return false;
}
