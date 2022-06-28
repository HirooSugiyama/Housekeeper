/*
確認画面
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"

#include"ConfirmationScreen.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//画像拡大率
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_TEX_SCALE(2.f, 2.f);
//初期座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_TEX_INIT_POSITION(250.f, 250.f);

//文字描画
//共通処理
//拡大率
const float ConfirmationScreen::STRING_SCALE = 3.f;
//YES
//座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_YES_POSITION(700.f, 350.f);
//No
//座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_NO_POSITION =
STRING_YES_POSITION + DirectX::SimpleMath::Vector2(0.f, 60.f);


//確認画面用カーソルの基本情報
//拡大率
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_CURSOR_SCALE(0.25f, 0.25f);
//初期座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_CURSOR_INIT_POSITION =
STRING_NO_POSITION + DirectX::SimpleMath::Vector2(-50.f, -40.f);
//移動幅
const float ConfirmationScreen::CONFI_CURSOR_SHIFT = 60.f;


//文字テクスチャ
//拡大率
const  DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_TEXTURE_SCALE(1.f, 1.f);
//座標
const  DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_TEXTURE_POSITION =
CONFI_TEX_INIT_POSITION + DirectX::SimpleMath::Vector2(-250.f, -250.f);

//連続押し防止時間
const int ConfirmationScreen::CONTINUITY_STOP_TIME = 1;

/*===================================
コンストラクタ
引数：なし
===================================*/
ConfirmationScreen::ConfirmationScreen()
	:
	mpConfirTexture(),
	mpCursor(),
	mSelectFlag(true),	//true:Yes,false:No
	mpStringTexture(),
	mpTimer(nullptr)
{
	mpConfirTexture = std::make_unique<ObjectTexture>();
	mpCursor = std::make_unique<Cursor>();
	mpStringTexture = std::make_unique<ObjectTexture>();
	mpTimer = std::make_unique<Timer>();
}

/*==================================
デストラクタ
===================================*/
ConfirmationScreen::~ConfirmationScreen()
{
}

/*===================================
初期化処理
引数：描画文字画像の鍵
返り値：なし
===================================*/
void ConfirmationScreen::Initialize(const int& stringTexturekey)
{
	//初期化処理
	mpConfirTexture->Initialize();
	mpStringTexture->Initialize();

	//リソースの取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__CONFIRMATION));

	//画像の設定
	mpConfirTexture->SetTexture(texture);

	texture = pRM->GetTexture(stringTexturekey);
	mpStringTexture->SetTexture(texture);


	//拡大率の設定
	mpConfirTexture->SetScale(CONFI_TEX_SCALE);
	mpStringTexture->SetScale(STRING_TEXTURE_SCALE);

	//座標の設定
	mpConfirTexture->SetPosition(CONFI_TEX_INIT_POSITION);
	mpStringTexture->SetPosition(STRING_TEXTURE_POSITION);

	//カーソルの初期化処理
	mpCursor->Initialize(
		static_cast<int>(StageSelectTexturesResouce::TEXTURE__CURSOR),
		CONFI_CURSOR_INIT_POSITION,
		CONFI_CURSOR_SCALE,
		CONFI_CURSOR_SHIFT);

	//タイマーの設定処理
	mpTimer->SetMaxTime(CONTINUITY_STOP_TIME);
	mpTimer->ResetMainTimer();

	//リセット処理
	this->Reset();
}

/*==================================
リセット処理
引数：なし
返り値：なし
===================================*/
void ConfirmationScreen::Reset()
{
	//カーソルの位置初期化処理
	mpCursor->CursorReset();

	//タイマーを初期化
	mpTimer->ResetMainTimer();

	//現在選択しているカーソルをYesにリセット
	mSelectFlag = true;
}


/*=================================
描画処理
引数：なし
返り値；時間フラグ
===================================*/
bool ConfirmationScreen::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//連続押し防止の時間測定
	bool timerFlag = mpTimer->Update();
	if (!timerFlag)return false;

	//↓が押され、現在の選択肢がNoだった場合
	if ((pKey->SelectOver() || pGamePad->ChangeCursorUp()) && !mSelectFlag)
	{
		//Yesとする
		mSelectFlag = true;

		//カーソルを移動する
		mpCursor->CursorUp();
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//↑が押され、現在の選択肢がYesだった場合
	else if ((pKey->SelectUnder() || pGamePad->ChangeCursorDown()) && mSelectFlag)
	{
		//Noとする
		mSelectFlag = false;
		//カーソルを移動する
		mpCursor->CursorDown();
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	return true;
}

/*==================================
描画処理
引数：点滅フラグ
返り値：なし
===================================*/
void ConfirmationScreen::Draw(const bool& blinkingFlag)
{
	//画像の描画
	mpConfirTexture->Draw();
	mpStringTexture->Draw();


	//時間が来ていなかったら
	if (mpTimer->GetMainTimer() < mpTimer->GetMaxTime())
	{
		//文字の描画処理
		this->DrawString(true);
	}
	//選択可能な場合
	else
	{
		//描画処理
		mpCursor->Draw(true);
		//文字の描画処理
		this->DrawString(blinkingFlag);
	}	
}

/*==================================
文字の描画処理:private
引数：点滅フラグ
返り値：なし
===================================*/
void ConfirmationScreen::DrawString(const bool& blinkingFlag)
{
	//選択肢がYesの時点滅させる
	if (mSelectFlag)
	{
		if (blinkingFlag)
		{
			//[Yes]の描画
			Utility::DrawString
			(
				L" Yes",
				STRING_YES_POSITION,
				DirectX::Colors::Black,
				STRING_SCALE
			);

		}
		//[No]の描画
		Utility::DrawString
		(
			L" No",
			STRING_NO_POSITION,
			DirectX::Colors::Black,
			STRING_SCALE
		);
	}
	else
	{
		//[Yes]の描画
		Utility::DrawString
		(
			L" Yes",
			STRING_YES_POSITION,
			DirectX::Colors::Black,
			STRING_SCALE
		);

		if (blinkingFlag)
		{
			//[No]の描画
			Utility::DrawString
			(
				L" No",
				STRING_NO_POSITION,
				DirectX::Colors::Black,
				STRING_SCALE
			);
		}
	}
}
