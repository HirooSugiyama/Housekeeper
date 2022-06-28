/*
ポーズ
作成者：杉山
作成日：2021/09/30
*/

#include"pch.h"
#include"Pause.h"

//所持元
#include"../PlayScene.h"
#include"../../UI/UI.h"

//拡大率
const DirectX::SimpleMath::Vector2 Pause::SELECT_CURSOR_SCALE(0.25f, 0.25f);
//初期座標
const DirectX::SimpleMath::Vector2 Pause::SELECT_CURSOR_INIT_POSITION(570.f, 445.f);
//移動幅
const float Pause::SELECT_CURSOR_SHIFT = 108.f;

//文字描画位置
const DirectX::SimpleMath::Vector2 Pause::SELECT_STRING_ON_POS(923, 305);

const DirectX::SimpleMath::Vector2 Pause::SELECT_STRING_SLASH_POS = SELECT_STRING_ON_POS + 
													DirectX::SimpleMath::Vector2(110.f, 0.f);

const DirectX::SimpleMath::Vector2 Pause::SELECT_STRING_OFF_POS = SELECT_STRING_SLASH_POS +
													DirectX::SimpleMath::Vector2(40.f, 0.f);

/*=====================
コンストラクタ
引数：なし
=====================*/
Pause::Pause()
	:
	mpPlayScene(nullptr),
	mpTexture(nullptr),
	mpCursor(nullptr),
	mState(static_cast<int>(SelectState::KEEP)),
	mControlUIDrawFlag(true)
{
	mpTexture = std::make_unique<ObjectTexture>();
	mpCursor = std::make_unique<Cursor>();
}

/*=====================
デストラクタ
=====================*/
Pause::~Pause()
{
}

/*===============================
初期化処理
引数：プレイシーンのポインタ
返り値：なし
===============================*/
void Pause::Initialize(PlayScene* pPlayScene, UI* pUI)
{
	//ポインタの保存
	mpPlayScene = pPlayScene;
	mpUI = pUI;

	auto pResouceManager = ResourceManager::GetInstance();
	auto texture = pResouceManager->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__PAUSE));

	//画像の設定
	mpTexture->SetTexture(texture);
	mpTexture->Initialize();

	//カーソルの初期化処理
	mpCursor->Initialize(
		static_cast<int>(PlayTexturesResouce::TEXTURE__CURSOR),
		SELECT_CURSOR_INIT_POSITION,
		SELECT_CURSOR_SCALE,
		SELECT_CURSOR_SHIFT);
}

/*=====================
更新処理
引数：なし
返り値：終了フラグ
=====================*/
bool Pause::Update()
{
	//カーソルの位置設定
	this->MoveCursor();

	//実行処理
	switch (this->Execution())
	{
		case SelectState::CONFIG_CONTROL:
		{
			//UI描画を切り替える			
			this->UpdateControlUI();

			return false;
			break;
		}
		case SelectState::KEEP:
		{
			return true;
			break;
		}
		case SelectState::RETRY:
		{
			mpPlayScene->SetRetryFlag(true);
			return true;
			break;
		}
		case SelectState::TO_STAGE_SELECT:
		{
			mpPlayScene->SetClearFlag(true);
			return true;
			break;
		}
		
		case SelectState::NONE:
		{
			return false;
			break;
		}
	}
	return false;
}

/*===============================
描画処理
引数：なし
返り値：なし
===============================*/
void Pause::Draw()
{
	//画像の描画
	mpTexture->Draw();

	//カーソルの描画
	mpCursor->Draw();

	//操作UIの文字描画
	this->DrawControlUIString();

}

/*=====================
カーソル移動:private
引数：なし
返り値：なし
=====================*/
void Pause::MoveCursor()
{
	//キー入力を取得
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//カーソルを上に
	if (pKey->SelectOver() || pGamePad->ChangeCursorUp())
	{
		//最大値ではなかったら
		if (static_cast<SelectState>(mState) > SelectState::CONFIG_CONTROL)
		{
			//カーソルを更新
			mState--;
			mpCursor->CursorUp(); 
		}
	}
	//カーソルを下に
	if (pKey->SelectUnder() || pGamePad->ChangeCursorDown())
	{
		//最小値ではなかったら
		if (static_cast<SelectState>(mState)< SelectState::TO_STAGE_SELECT)
		{
			//カーソルを更新
			mState++;
			mpCursor->CursorDown();
		}
	}
}

/*==========================
現在の状態を実行:private
引数：なし
返り値：現在の状態
===========================*/
Pause::SelectState Pause::Execution()
{
	//キー入力を取得
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//決定が押されなかったら処理をしない
	if ((pKey->Decision() || pGamePad->Decision()))
	{
		return static_cast<SelectState>(mState);
	}	

	return SelectState::NONE;
}

/*==========================
UI描画処理:private
引数：なし
返り値：なし
===========================*/
void Pause::UpdateControlUI()
{
	//UI描画を切り替える
	mpUI->ChangeDrawControlUIFlag();

	//現在の状態を調べ、このクラスの管理フラグを設定する
	if (mpUI->GetDrawControlUIFlag())
	{
		mControlUIDrawFlag = true;
	}
	else
	{
		mControlUIDrawFlag = false;
	}
}

/*==========================
操作UIの文字描画:private
引数：なし
返り値：なし
===========================*/
void Pause::DrawControlUIString()
{
	//色指定
	DirectX::SimpleMath::Vector4 onColor = DirectX::Colors::White;
	DirectX::SimpleMath::Vector4 offColor = DirectX::Colors::White;

	if (mControlUIDrawFlag)
	{
		onColor = DirectX::Colors::Red;
	}
	else
	{
		offColor = DirectX::Colors::Red;
	}


	Utility::DrawString(L"ON", SELECT_STRING_ON_POS, onColor);
	Utility::DrawString(L"/", SELECT_STRING_SLASH_POS);
	Utility::DrawString(L"OFF", SELECT_STRING_OFF_POS, offColor);

}
