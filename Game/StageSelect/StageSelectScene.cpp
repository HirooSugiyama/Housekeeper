/*
ステージ選択シーン
作成者：杉山
作成日：2021/10/21
*/

#include "pch.h"

#include "../GameMain.h"
#include "DeviceResources.h"

#include "StageSelectScene.h"


//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//Master版フラグ
#include"Game/Master.h"



//タグの初期座標
const DirectX::SimpleMath::Vector2 StageSelectScene::TAG_INIT_POSITION(113.f, 145.f);
//幅
const float StageSelectScene::TAG_SHIFT = 100.f;
//確認画面用カーソルの基本情報
//拡大率
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_SCALE(0.25f, 0.25f);
//初期座標
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_INIT_POSITION(60.f, 150.f);
//移動幅
const float StageSelectScene::SELECT_CURSOR_SHIFT = 100.f;

//題の位置
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_POSITION(450.f,15.f);
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_SCALE(0.5f, 0.5f);

/*=========================================
コンストラクタ
引数：なし
=========================================*/
StageSelectScene::StageSelectScene()
	:
	mSelectNum(1),
	mpCursor(),
	mpStageInfo(),
	mpTag(),
	mpConfirmationScreen(),
	mpTextureBlinking(),
	mSelectFlag(false),
	mBGMID(Utility::EXCEPTION_NUM),
	mpCloud(nullptr),
	mpStageSelectNameTexture(nullptr),
	mpSignBoard(nullptr)
	

{
	mpCursor = std::make_unique<Cursor>();
	mpStageInfo = std::make_unique<StageInfomation>();
	mpConfirmationScreen = std::make_unique<ConfirmationScreen>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpCloud = std::make_unique<Cloud>();
	mpStageSelectNameTexture = std::make_unique<ObjectTexture>();
	mpSignBoard = std::make_unique<StageLevelSignBoard>();
	

	for (int i = 0; i< SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i] = std::make_unique<StageNumberTag>();
	}
}
/*========================================
デストラクタ
=========================================*/
StageSelectScene::~StageSelectScene()
{

}

/*=========================================
初期化
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::Initialize()
{
	// リソース関係の初期設定
	//リソースマネージャに画像を保存する
	auto pRM = ResourceManager::GetInstance();
	//データ初期化
	pRM->Finalize();
	//リソースの読み込み
	pRM->Load(ReadRange::STAGESELECT_TEXTURES_RESOUCE);

	//ステージ番号取得
#ifdef MASTER
	//ステージ番号を最大番号に
	mSelectNum = static_cast<int>(eSelectNum::_1);
	mMaxSelectStageNumber = static_cast<int>(eSelectNum::NUM) - 1;
#else
	//選択する番号はファイルから取得
	mSelectNum = this->GetFirstSelectStageNum();
	mMaxSelectStageNumber = this->GetFirstSelectStageNum();
#endif

	// テクスチャの読み込み
	mpTexture = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGESELECT));

	mpStageSelectNameTexture->SetTexture(pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGESELECTNAME)));
	mpStageSelectNameTexture->Initialize();
	mpStageSelectNameTexture->SetPosition(NAME_POSITION);
	mpStageSelectNameTexture->SetScale(NAME_SCALE);

	//カーソルの初期化処理
	mpCursor->Initialize(
		static_cast<int>(StageSelectTexturesResouce::TEXTURE__CURSOR),
		SELECT_CURSOR_INIT_POSITION,
		SELECT_CURSOR_SCALE,
		SELECT_CURSOR_SHIFT);

	//ステージ各種情報の初期化処理
	mpStageInfo->Initialize();

	for (int i = 0;  i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->Initialize();
	}
	//確認画面の初期化処理
	mpConfirmationScreen->Initialize(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STRINGJAPANISE));

	//曲を流す
	this->PlayBGM();

	//雲の初期化処理
	mpCloud->Initialize(static_cast<int>(StageSelectTexturesResouce::TEXTURE__CLOUD));

	//看板の初期設定
	mpSignBoard->Initialize();

	//マスター版でないときのみ処理を通す
#ifndef MASTER

	//カーソルの位置を設定する
	int shiftNum = 0;
	if (mSelectNum >= static_cast<int>(eSelectNum::_7))
	{
		shiftNum = mSelectNum - static_cast<int>(eSelectNum::_6);
	}
	else
	{
		shiftNum = mSelectNum;
	}
	for (int i = 1; i < shiftNum; i++)
	{
		mpCursor->CursorDown();
	}
#else
	//カーソルの位置を設定する
	int shiftNum = 0;

	//ファイルから最後に遊んだ番号を取得
	mSelectNum = this->GetFirstSelectStageNum();

	if (mSelectNum >= static_cast<int>(eSelectNum::_7))
	{
		shiftNum = mSelectNum - static_cast<int>(eSelectNum::_6);
	}
	else
	{
		shiftNum = mSelectNum;
	}

	for (int i = 1; i < shiftNum; i++)
	{
		mpCursor->CursorDown();
	}


#endif

	//ステージ番号を設定する
	this->SetNumberTag();

}

/*=========================================
更新
引数	：タイマーのヘルパー関数
戻り値	：次のシーン番号
=========================================*/
eGameScene StageSelectScene::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//ステージ選択
	this->StageSelect();

	//点滅処理
	mpTextureBlinking->Update();

	//雲の更新処理
	mpCloud->Update();

	//選択画面なら
	if (mSelectFlag)
	{
		//確認画面の更新処理
		bool timerFlag = mpConfirmationScreen->Update();

		//まだ時間でなければ処理をしない
		if (!timerFlag)	return eGameScene::NONE;

	}
	


	if (pKey->Decision()|| pGamePad->Decision())		//決定
	{	
		//確認画面ならば
		if (mSelectFlag)
		{
			if (mpConfirmationScreen->GetSelectFlag())
			{
				//プレイシーンへ
				//ステージ選択画面からの情報共有管理クラスの取得
				auto& pStoP = StoPSceneComponent::GetStoPIFInstance();

				pStoP.SetStageCSV(this->SetFileName());
				//ステージ番号も同時に保存しておく
				pStoP.SetStageNumber(std::to_string(mSelectNum));

				ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
				//曲を止める
				this->StopBGM();

				auto& pSTI = ScreenTransitionComponent::GetScreenTransitionInstance();
				pSTI.SetFadeUseFlag(true);
				pSTI.GetFade()->SetClose();

				return eGameScene::PLAY;	//直接プレイシーンへ
			}
			else
			{
				//確認画面用カーソルのタイマーをリセットする
				mpConfirmationScreen->Reset();

				//確認用画面を消す
				mSelectFlag = false;
			}
			
		}
		else
		{

			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
			mSelectFlag = true;

			//リセット処理
			mpConfirmationScreen->Reset();
		}		
	}

	return eGameScene::NONE;
}

/*=======================================
描画
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::Draw()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	//描画開始
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);
	
	DirectX::SimpleMath::Vector2 position{ 0.f,0.f };

	//背景画像の描画
	pDxIF.GetSpriteBatch()->Draw(mpTexture.Get(), position);

	//看板の描画
	mpSignBoard->Draw();

	//雲の描画処理
	mpCloud->Draw();

	//題の描画
	mpStageSelectNameTexture->Draw();
	

	//選択画面ではないなら
	if (!mSelectFlag)
	{
		//カーソルの描画
		mpCursor->Draw();

		//ステージ情報の描画
		mpStageInfo->Draw(mSelectNum);

		//ステージ番号を仮保存
		int stageScreenNum = mSelectNum;
		//もし2画面目以降のステージなら
		if (stageScreenNum >= static_cast<int>(eSelectNum::_7))
		{
			//1画面分値を減らす
			stageScreenNum -= static_cast<int>(eSelectNum::_6);
		}

		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//現在選択できないステージは消す
			if (i >= mMaxSelectStageNumber)continue;

			//選択しているステージのみ点滅させる
			if (stageScreenNum - 1 == i)
			{
				
				mpTag[i]->Draw(mpTextureBlinking->GetBlinkingFlag());
			}
			else
			{
				//それ以外は通常描画
				mpTag[i]->Draw();
			}
		}
	}
	else
	{
		//カーソルの描画
		mpCursor->Draw();

		//ステージ情報の描画
		mpStageInfo->Draw(mSelectNum);
		//各ステージ番号の描画
		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//現在選択できないステージは消す
			if (i >= mMaxSelectStageNumber)continue;

			//それ以外は通常描画
			mpTag[i]->Draw();
		}
		mpConfirmationScreen->Draw(mpTextureBlinking->GetBlinkingFlag());
	}

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
終了処理
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::Finalize()
{
	const auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();
}


/*=========================================
モード選択:private
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::StageSelect()
{
	//選択画面なら処理を行わない
	if (mSelectFlag)return;

	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver() || pGamePad->ChangeCursorUp())
	{
		//カーソルを上げる
		this->CursorUp();
	}

	if (pKey->SelectUnder() || pGamePad->ChangeCursorDown())
	{
		//カーソルを下げる
		this->CursorDown();
	}
}


/*=========================================
ファイル名算出:private
引数：なし
返り値：ファイルの相対パス
=========================================*/
std::string StageSelectScene::SetFileName()
{
	std::string filePath = "Resources/CSV/";
	std::string fileName = "PlayScene" + std::to_string(mSelectNum);
	std::string expand = ".csv";
	std::string fullFilePath="none";

	fullFilePath = filePath + fileName + expand;
	return fullFilePath;
}

/*=========================================
カーソルをあげる:private
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::CursorUp()
{
	//最大ステージ数ではないなら処理を通す
	if (mSelectNum - 1 != static_cast<int>(eSelectNum::NONE))
	{
		//画像を上へ
		mpCursor->CursorUp();
		mSelectNum--;
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//画面で一番上の選択肢になったらカーソル位置をリセットする
	if (mSelectNum == static_cast<int>(eSelectNum::_7))
	{
		mpCursor->CursorReset();
		//ステージ番号を保存する
		this->SetNumberTag();
	}
	//画面で一番下の選択肢になったら指定の位置にカーソルをセットする
	if (mSelectNum == static_cast<int>(eSelectNum::_6))
	{
		mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
		//ステージ番号を保存する
		this->SetNumberTag();
	}
}

/*=========================================
カーソルをさげる:private
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::CursorDown()
{
	//最小ステージ数ではないなら処理を通す
	if (mSelectNum + 1 != static_cast<int>(eSelectNum::NUM) && mSelectNum + 1 <= mMaxSelectStageNumber)
	{
		//画像を下へ
		mpCursor->CursorDown();
		mSelectNum++;
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//画面で一番上の選択肢になったらカーソル位置をリセットする
	if (mSelectNum == static_cast<int>(eSelectNum::_7))
	{
		mpCursor->CursorReset();
		//ステージ番号を保存する
		this->SetNumberTag();
	}
	//画面で一番下の選択肢になったら指定の位置にカーソルをセットする
	if (mSelectNum == static_cast<int>(eSelectNum::_6))
	{
		mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
		//ステージ番号を保存する
		this->SetNumberTag();
	}
}

/*========================================
番号を設定する:private
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::SetNumberTag()
{
	int index = 0;
	int stagenum = 0;
	//リセットする
	for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->SetStageNum(Utility::EXCEPTION_NUM);
	}
	
	//上半分なら
	if (mSelectNum <= static_cast<int>(eSelectNum::_6))
	{
		stagenum = static_cast<int>(eSelectNum::_1);
	}
	else 
	{
		stagenum = static_cast<int>(eSelectNum::_7);
	}

	//リセットする
	for (index; index < SCREEN_STEGE_MAX_NUM; index++,stagenum++)
	{
		//マスター版でないときのみ処理を通す
#ifndef MASTER
		if (stagenum  > this->GetFirstSelectStageNum())
		{
			break;
		}
#else
		if (stagenum > static_cast<int>(eSelectNum::NUM) - 1)
		{
			break;
		}
#endif
		mpTag[index]->SetStageNum(stagenum);

		mpTag[index]->SetPosition(TAG_INIT_POSITION+ DirectX::SimpleMath::Vector2(0.f,(index *TAG_SHIFT)));

	}

}

/*=========================================
ステージ番号取得:private
引数：なし
返り値：ステージ番号
=========================================*/
int StageSelectScene::GetFirstSelectStageNum()
{
	//例外処理
	Utility::FileError(Utility::NEXT_STAGE_NUM_FILEPATH);

	//ファイル変換
	std::ifstream ifs(Utility::NEXT_STAGE_NUM_FILEPATH);
	//1文字の情報を保存する変数
	std::string stageNum{};

	//呼び出し
	std::getline(ifs, stageNum);

	return atoi(stageNum.c_str());
}

/*=========================================
音楽を流す:private
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_STAGESELECT);
}

/*=========================================
音楽を止める:private
引数：なし
返り値：なし
=========================================*/
void StageSelectScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
