/*
ポーズ
作成者：杉山
作成日：2021/09/30
*/
#pragma once


//所持
#include"../../Common/ObjectTexture.h"
#include"../../Common/Cursor.h"

class PlayScene;
class UI;

class Pause 
{
private:

	//現在の状態
	enum class SelectState:int
	{
		CONFIG_CONTROL,
		KEEP,
		RETRY,
		TO_STAGE_SELECT,
		NONE
	};

	//確認画面用カーソルの基本情報
	//拡大率
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_SCALE;
	//初期座標
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_INIT_POSITION;
	//移動幅
	static const float SELECT_CURSOR_SHIFT;

	//文字描画位置
	static const DirectX::SimpleMath::Vector2 SELECT_STRING_ON_POS;
	static const DirectX::SimpleMath::Vector2 SELECT_STRING_SLASH_POS;
	static const DirectX::SimpleMath::Vector2 SELECT_STRING_OFF_POS;

	//保存用のポインタ
	PlayScene* mpPlayScene;
	UI* mpUI;

	//UIまとめ画像
	std::unique_ptr<ObjectTexture> mpTexture;
	//カーソル
	std::unique_ptr<Cursor> mpCursor;

	//現在の状態
	int mState;

	//UI描画フラグ
	bool mControlUIDrawFlag;

public:
	//コンストラクタ
	Pause();

	//デストラクタ
	~Pause();
	
	//初期化
	void Initialize(PlayScene* pPlayScene,UI* pUI);

	//更新
	bool Update();

	//描画
	void Draw();

private:
	//カーソル移動
	void MoveCursor();

	//実行
	SelectState Execution();

	//UI描画処理
	void UpdateControlUI();

	//操作UIの文字描画
	void DrawControlUIString();

};