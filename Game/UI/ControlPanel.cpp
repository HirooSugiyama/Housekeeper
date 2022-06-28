/*
操作方法描画UI
作成者：杉山
作成日：2022/01/30
*/
#include"pch.h"

#include"ControlPanel.h"

//定数群
#include"ControlPanelConstant.h"


/*===================================
コンストラクタ
引数：なし
===================================*/
ControlPanel::ControlPanel()
	:
	mpMove(),
	mpAttack(),
	mpChange(),
	mpPause(),
	mpReStart(),
	mDrawFlag(true)
{
	mpMove = std::make_unique<ObjectSpriteTexture>();
	mpAttack = std::make_unique<ObjectSpriteTexture>();
	mpChange = std::make_unique<ObjectSpriteTexture>();
	mpPause = std::make_unique<ObjectSpriteTexture>();
	mpReStart = std::make_unique<ObjectSpriteTexture>();
}

/*===================================
デストラクタ
===================================*/
ControlPanel::~ControlPanel()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void ControlPanel::Initialize()
{
	//リソースマネージャからリソースを取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__CONTROLSPRITE));

	//初期化処理
	mpMove->Initialize();
	mpAttack->Initialize();
	mpChange->Initialize();
	mpPause->Initialize();
	mpReStart->Initialize();

	//画像設定処理
	mpMove->SetTexture(texture);
	mpAttack->SetTexture(texture);
	mpChange->SetTexture(texture);
	mpPause->SetTexture(texture);
	mpReStart->SetTexture(texture);

	//座標設定処理
	mpMove->SetPosition(ControlPanelConstant::MOVE_POS);
	mpAttack->SetPosition(ControlPanelConstant::ATTACK_POS);
	mpChange->SetPosition(ControlPanelConstant::CHANGE_POS);
	mpPause->SetPosition(ControlPanelConstant::PAUSE_POS);
	mpReStart->SetPosition(ControlPanelConstant::RESTART_POS);

	//座標設定処理
	mpMove->SetScale(ControlPanelConstant::TEX_SCALE);
	mpAttack->SetScale(ControlPanelConstant::TEX_SCALE);
	mpChange->SetScale(ControlPanelConstant::TEX_SCALE);
	mpPause->SetScale(ControlPanelConstant::TEX_SCALE);
	mpReStart->SetScale(ControlPanelConstant::TEX_SCALE);

	//画像切り取り位置を指定
	mpMove->SetRect(ControlPanelConstant::MOVE_RECT);
	mpAttack->SetRect(ControlPanelConstant::ATTACK_RECT);
	mpChange->SetRect(ControlPanelConstant::CHANGE_RECT);
	mpPause->SetRect(ControlPanelConstant::PAUSE_RECT);
	mpReStart->SetRect(ControlPanelConstant::RESTART_RECT);

}

/*==================================
描画処理
引数：なし
返り値：なし
===================================*/
void ControlPanel::Draw()
{
	//描画フラグが降りている場合処理をしない
	if (!mDrawFlag)return;

	//描画処理
	mpMove->Draw();
	mpAttack->Draw();
	mpChange->Draw();
	mpPause->Draw();
	mpReStart->Draw();
}

/*===================================
ゲームパッドとキーを切り替え
引数：なし
返り値：なし
===================================*/
void ControlPanel::ChangeControl()
{
	//ゲームパッド使用状況を取得
	GamePadTracker* pGamePadTracker = GamePadTracker::GetGamePadTrackerInstance();

	//使用中の処理
	if (pGamePadTracker->GetUseFlag())
	{
		//画像切り取り位置を指定
		RECT rect = ControlPanelConstant::MOVE_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpMove->SetRect(rect);

		rect = ControlPanelConstant::ATTACK_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpAttack->SetRect(rect);

		rect = ControlPanelConstant::CHANGE_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpChange->SetRect(rect);

		rect = ControlPanelConstant::PAUSE_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpPause->SetRect(rect);
		rect = ControlPanelConstant::RESTART_RECT;
		rect.top = ControlPanelConstant::GAMEPAD_TOP;
		rect.bottom = ControlPanelConstant::GAMEPAD_BOTTOM;
		mpReStart->SetRect(rect);
	}
	//未使用時の処理
	else
	{
		//画像切り取り位置を指定
		mpMove->SetRect(ControlPanelConstant::MOVE_RECT);
		mpAttack->SetRect(ControlPanelConstant::ATTACK_RECT);
		mpChange->SetRect(ControlPanelConstant::CHANGE_RECT);
		mpPause->SetRect(ControlPanelConstant::PAUSE_RECT);
		mpReStart->SetRect(ControlPanelConstant::RESTART_RECT);
	}
}
