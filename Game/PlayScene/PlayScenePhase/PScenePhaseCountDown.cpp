/*
カウントダウンフェーズ
作成者：杉山
作成日：2021/09/30
*/

#include"pch.h"
#include"PScenePhaseCountDown.h"

//所持元
#include"../PlayScene.h"

//前方宣言
#include"../PlaySceneCommon/Administrator/Timer.h"

//関数内部の使用
#include"Libraries/MyLibraries/Camera.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"

//カウントダウン時間
const int PScenePhaseCountDown::CountDown_MAX_NUM = 3;

//画面中央値
const DirectX::SimpleMath::Vector2 PScenePhaseCountDown::WINDOW_CENTER(1280.f / 2.f, 780.f / 2.f);


/*=====================
コンストラクタ
引数：なし
=====================*/
PScenePhaseCountDown::PScenePhaseCountDown()
	:
	mpPlayScene(nullptr),
	mpCountDownTimer(nullptr),
	mpCountDownString(nullptr)
{
	mpCountDownTimer = std::make_unique<Timer>();
	mpCountDownString = std::make_unique<SpriteNumber2D>();
}

/*=====================
デストラクタ
=====================*/
PScenePhaseCountDown::~PScenePhaseCountDown()
{
}

/*===============================
初期化処理
引数：所有先のポインタ
返り値：なし
===============================*/
void PScenePhaseCountDown::Initialize(PlayScene* pPlayScene)
{
	//ポインタの保存
	mpPlayScene = pPlayScene;

	//カウントダウン最大時間を設定する
	mpCountDownTimer->SetMaxTime(CountDown_MAX_NUM);

	mpCountDownString->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING));
	mpCountDownString->Initialize();

	mpCountDownString->SetScale(Utility::STRING_SIZE_MEDIUM);
}

/*=====================
更新処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseCountDown::Update()
{
	//時間判定用変数
	bool flag = mpCountDownTimer->Update();

	//プレイヤーの位置情報を摘出
	DirectX::SimpleMath::Vector3 playerpos =
		PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();
	
	//カメラの更新
	mpPlayScene->GetCameraPointer()->Update(playerpos);
	

	//もしカウントダウンが終わったら
	if (flag)
	{
		//次のStateへ
		mpPlayScene->ChangePhaseToDefence();
		mpPlayScene->GetPhase()->Reset();
	}
}

/*===============================
描画処理
引数：なし
返り値：なし
===============================*/
void PScenePhaseCountDown::Draw()
{
	//カウントダウンを描画する
	int drawNum = mpCountDownTimer->GetMaxTime() - mpCountDownTimer->GetMainTimer();

	mpCountDownString->Create(drawNum, WINDOW_CENTER);
	mpCountDownString->Draw();
}

/*=====================
描画処理
引数：なし
返り値：なし
=====================*/
void PScenePhaseCountDown::Reset()
{
	//カメラを変更
	mpPlayScene->ChangeMainCamera();

	//カメラ行列を取得
	auto& pPVIf = CameraInfoComponent::GetCameraInfoComponentInstance();

	//定点カメラに変更する
	pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
	pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
}
