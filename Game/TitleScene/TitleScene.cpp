/*
タイトルシーン
作成者：杉山
作成日：2021/10/21
*/

#include "pch.h"

#include "../GameMain.h"
#include "DeviceResources.h"
#include "TitleScene.h"
#include"Game/Common/Cloud.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"

//ロゴの座標
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_LOGO_POSITION(190.f, 160.f);
//開始ボタン位置
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_START_BAR_POSITION(450.f,450.f);


//タイトルバー初期切り取り位置
const RECT TitleScene::TITLE_BAR_INIT_RECT{ 0,0,396,143 };

/*=======================================
コンストラクタ
引数：なし
=========================================*/
TitleScene::TitleScene()
	:
	mpCloud(),
	mBGMID(Utility::EXCEPTION_NUM),
	mpTitleBar(nullptr)
{
	//雲の生成
	mpCloud = std::make_unique<Cloud>();
	mpTitleBar = std::make_unique<ObjectSpriteTexture>();
}

/*=========================================
デストラクタ
=========================================*/
TitleScene::~TitleScene()
{
}

/*=========================================
初期化
引数：なし
返り値：なし
=========================================*/
void TitleScene::Initialize()
{
	// リソース関係の初期設定
	//リソースマネージャに画像を保存する
	auto pRM = ResourceManager::GetInstance();
	//データ初期化
	pRM->Finalize();
	//リソースの読み込み
	pRM->Load(ReadRange::TITLE_TEXTURES_RESOUCE);

	// テクスチャの読み込み
	mpTexture = pRM->GetTexture(static_cast<int>(TitleTexturesResouce::TEXTURE__TITLE_BACKGROUND));
	mpLogo = pRM->GetTexture(static_cast<int>(TitleTexturesResouce::TEXTURE__TITLENAME));
	
	//動く雲の初期化処理
	mpCloud->Initialize(static_cast<int>(TitleTexturesResouce::TEXTURE__CLOUD));

	auto texture= pRM->GetTexture(static_cast<int>(TitleTexturesResouce::TEXTURE__TITLEBAR));
	mpTitleBar->SetTexture(texture);
	mpTitleBar->Initialize();
	mpTitleBar->SetPosition(TITLE_START_BAR_POSITION);
	mpTitleBar->SetRect(TITLE_BAR_INIT_RECT);

	//BGMを流す
	this->PlayBGM();
}

/*=========================================
更新
引数	：タイマーのヘルパー関数
戻り値	：次のシーン番号
=========================================*/
eGameScene TitleScene::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//雲の更新処理
	mpCloud->Update();

	//入力機器判定処理
	this->ChangeControl();

	// サウンドの更新
	ADX2::GetInstance().Update();

	if (pKey->Decision()|| pGamePad->Decision())//キー入力が行われたら
	{
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
		//曲を止める
		this->StopBGM();
		return eGameScene::STAGE_SELECT;//次のシーンへ
	}

	return eGameScene::NONE;
}

/*=========================================
描画
引数：なし
返り値：なし
=========================================*/
void TitleScene::Draw()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	//描画開始
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);

	pDxIF.GetSpriteBatch()->Draw(mpTexture.Get(), DirectX::SimpleMath::Vector2::Zero);
	
	mpCloud->Draw();
	mpTitleBar->Draw();

	pDxIF.GetSpriteBatch()->Draw(mpLogo.Get(), TITLE_LOGO_POSITION);
	

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
終了処理
引数：なし
返り値：なし
=========================================*/
void TitleScene::Finalize()
{
	// リソース関係の初期化
	auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();
}

/*========================================
ゲームパッドとキーを切り替え:private
引数：なし
返り値：なし
=========================================*/
void TitleScene::ChangeControl()
{
	//ゲームパッド使用状況を取得
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	RECT rect = TITLE_BAR_INIT_RECT;

	//使用中の処理
	if (pGamePadTracker->GetUseFlag())
	{
		rect.top = TITLE_BAR_INIT_RECT.bottom;
		rect.bottom *= Utility::SHIFT_SPRITE_TEXTURE;
		mpTitleBar->SetRect(rect);
	}
	//パッド未使用時の処理
	else
	{
		mpTitleBar->SetRect(rect);
	}
}

/*========================================
音楽を流す:private
引数：なし
返り値：なし
=========================================*/
void TitleScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_TITLE);
}

/*=========================================
音楽を止める:private
引数：なし
返り値：なし
=========================================*/
void TitleScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
