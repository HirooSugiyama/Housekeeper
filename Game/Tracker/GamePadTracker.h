/*
コントローラーの取得(シングルトン)
作成者：杉山
作成日：2021/10/21
ボタン入力は極力数を増やしたくないので、敢えて追加しにくい形で作成しています。
*/

#pragma once

#include<GamePad.h>

class GamePadTracker
{
public:

	//自分自身の取得
	static GamePadTracker* GetGamePadTrackerInstance()
	{
		static GamePadTracker gpt;

		return &gpt;
	}

private:

	//プレイヤー１
	static const int PLAYER_ONE;

	//使用するボタン一覧
	enum class eUseButton
	{
		LT,RT,				//上部トリガー

		RIGHT_STICK_LEFT,	//右スティック左入力
		RIGHT_STICK_RIGHT,	//右スティック右入力
		RIGHT_STICK_UP,		//右スティック上入力
		RIGHT_STICK_DOWN,	//右スティック下入力

		LEFT_STICK_LEFT,	//左スティック左入力
		LEFT_STICK_RIGHT,	//左スティック右入力
		LEFT_STICK_UP,		//左スティック上入力
		LEFT_STICK_DOWN,	//左スティック下入力

		X,Y,B,A,			//コマンドボタン


		BACK,				//戻るボタン
		START,				//開始ボタン
		XBOX_BUTTON			//Xboxボタン
	};


	//トラッカー
	DirectX::GamePad::ButtonStateTracker  mTracker;

	// ボタン
	std::unique_ptr<DirectX::GamePad> mpGamePad;

	//使用フラグ
	bool mGamePadUseFlag;


	//コピーコンストラクタ、コピー代入演算子をdelete。
	GamePadTracker(const GamePadTracker & kt) = delete;
	GamePadTracker operator=(const GamePadTracker& kt) = delete;

	//コンストラクタ
	GamePadTracker();
	//デストラクタ
	~GamePadTracker() = default;

	//ボタン操作(ベースとなる関数)
	bool PushButton(eUseButton button);
	bool PressButton(eUseButton button);

	//強制終了
	bool Quit() { return this->PushButton(eUseButton::XBOX_BUTTON); }

public:
	//更新処理
	void ButtonUpdate();

	//使用用途の数だけ関数を作成する

	//決定
	bool Decision() { return this->PushButton(eUseButton::B); }
	//戻る
	bool Back() { return this->PushButton(eUseButton::A); }

	//カーソル移動
	bool ChangeCursorDown() { return this->PushButton(eUseButton::LEFT_STICK_DOWN); }
	bool ChangeCursorUp() { return this->PushButton(eUseButton::LEFT_STICK_UP); }


	//移動
	bool MoveLeft() { return this->PressButton(eUseButton::LEFT_STICK_LEFT); }
	bool MoveRight() { return this->PressButton(eUseButton::LEFT_STICK_RIGHT); }
	bool MoveUp() { return this->PressButton(eUseButton::LEFT_STICK_UP); }
	bool MoveDown() { return this->PressButton(eUseButton::LEFT_STICK_DOWN); }
	bool Move()
	{
		return this->MoveLeft() || this->MoveRight() || this->MoveUp() || this->MoveDown();
	}
	
	//プレイヤーの状態変更
	bool ChangePlayerActionLeft() { return this->PushButton(eUseButton::RIGHT_STICK_LEFT); }
	bool ChangePlayerActionRight(){return this->PushButton(eUseButton::RIGHT_STICK_RIGHT);}

	//プレイヤーの武器変更
	bool ChangePlayerWeapon()
	{
		return this->PushButton(eUseButton::RIGHT_STICK_LEFT) || this->PushButton(eUseButton::RIGHT_STICK_RIGHT);
	}

	//プレイヤーの行動ボタン
	bool ActionPlayer() { return this->PressButton(eUseButton::RT); }

	bool AttackStrongPlayer() { return this->PushButton(eUseButton::RT); }

	//カメラ変更処理
	bool ChangeCamera() { return this->PushButton(eUseButton::LT); }

	//スキップ
	bool Skip() { return this->PushButton(eUseButton::B); }


	//使用フラグのアクセサ
	bool GetUseFlag() { return mGamePadUseFlag; }

	//ポーズ
	bool Pause() { return this->PushButton(eUseButton::BACK); }

	//リスタート
	bool ReStart() { return this->PushButton(eUseButton::START); }

private:

	//実行終了処理
	void ForcedTermination();
};