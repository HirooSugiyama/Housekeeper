/*
コントローラーの取得(シングルトン)
作成者：杉山
作成日：2021/10/21
ボタン入力は極力数を増やしたくないので、敢えて追加しにくい形で作成しています。
*/


#include"pch.h"
#include "GamePadTracker.h"

//プレイヤー１
const int GamePadTracker::PLAYER_ONE = 0;

/*==========================================================
コンストラクタ
引数：なし
==========================================================*/
GamePadTracker::GamePadTracker()
	:
	mTracker(),
	mpGamePad(nullptr),
	mGamePadUseFlag()
{
	// ボタン関連
	if (mpGamePad == nullptr)
	{
		mpGamePad = std::make_unique<DirectX::GamePad>();
	}	
}

/*========================================================
ボタン操作(ベースとなる関数)(単発押し処理)
引数：入力するボタン
返り値：true→押している	false→押されていない
==========================================================*/
bool GamePadTracker::PushButton(eUseButton button)
{
	//簡略化
	using ButtonState = DirectX::GamePad::ButtonStateTracker::ButtonState;

	switch (button)
	{
		//左ボタン
		case eUseButton::LT:
		{
			if (mTracker.leftTrigger == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}

		case eUseButton::RT:
		{
			if (mTracker.rightTrigger == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}

		//右スティック
		case eUseButton::RIGHT_STICK_LEFT:
		{
			if (mTracker.rightStickLeft == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::RIGHT_STICK_RIGHT:
		{
			if (mTracker.rightStickRight == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::RIGHT_STICK_UP:
		{
			if (mTracker.rightStickUp == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::RIGHT_STICK_DOWN:
		{
			if (mTracker.rightStickDown == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::LEFT_STICK_UP:
		{
			if (mTracker.leftStickUp == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::LEFT_STICK_DOWN:
		{
			if (mTracker.leftStickDown == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::B:
		{
			if (mTracker.b == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::A:
		{
			if (mTracker.a == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		

		//戻るボタン
		case eUseButton::BACK:
		{
			if (mTracker.back == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		//開始ボタン
		case eUseButton::START:
		{
			if (mTracker.start == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		//単発押ししないボタンが来た場合は処理を行わない
		default:
		{
			break;
		}
	}

	return false;
}

/*==========================================================
ボタン操作(ベースとなる関数)(長押し処理)
引数：入力するボタン
返り値：true→押している	false→押されていない
==========================================================*/
bool GamePadTracker::PressButton(eUseButton button)
{
	//簡略化
	using ButtonState = DirectX::GamePad::ButtonStateTracker::ButtonState;

	// ボタン入力情報を取得する
	auto buttonState = mpGamePad.get()->GetState(PLAYER_ONE);

	switch (button)
	{

		case eUseButton::RT:
		{
			if (mTracker.rightTrigger == ButtonState::HELD)
			{
				return true;
			}
			break;
		}

		case eUseButton::LEFT_STICK_LEFT:
		{
			if (mTracker.leftStickLeft == ButtonState::HELD)
			{
				return true;
			}
			break;
		}
		case eUseButton::LEFT_STICK_RIGHT:
		{
			if (mTracker.leftStickRight == ButtonState::HELD)
			{
				return true;
			}
			break;
		}
		case eUseButton::LEFT_STICK_UP:
		{
			if (mTracker.leftStickUp == ButtonState::HELD)
			{
				return true;
			}
			break;
		}		
		case eUseButton::LEFT_STICK_DOWN:
		{
			if (mTracker.leftStickDown == ButtonState::HELD)
			{
				return true;
			}
			break;
		}

		//長押ししないボタンが来た場合は処理を行わない
		default:
		{
			break;
		}
	}


	return false;
}
/*==========================================================
更新処理
引数：なし
返り値：なし
==========================================================*/
void GamePadTracker::ButtonUpdate()
{
	// ボタン入力情報を取得する
	auto buttonState = mpGamePad.get()->GetState(PLAYER_ONE);
	//接続チェック
	if (!buttonState.IsConnected())
	{
		mGamePadUseFlag = false;
		return;
	}

	//使用中とする
	mGamePadUseFlag = true;

	//トラッカー更新処理
	mTracker.Update(buttonState);

	//強制終了処理
	this->ForcedTermination();
}


/*==========================================================
実行終了処理
引数：なし
返り値：なし
==========================================================*/
void GamePadTracker::ForcedTermination()
{
	// ボタン入力情報を取得する
	auto buttonState = mpGamePad.get()->GetState(PLAYER_ONE);
	//もしBackボタンが押されたら
	if (this->Quit())
	{
		//強制終了する
		PostQuitMessage(0);
	}
}
