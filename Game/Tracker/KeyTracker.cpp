/*
キーボードトラッカーの取得(シングルトン)
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"
#include "KeyTracker.h"

/*==========================================================
コンストラクタ
引数：なし
==========================================================*/
KeyTracker::KeyTracker()
	:
	mKeybord(nullptr)
{
	// キーボード関連
	mKeybord = std::make_unique<DirectX::Keyboard>();
}

/*==========================================================
キー操作(ベースとなる関数)(単発押し処理)
引数：入力するキー
返り値：true→押している	false→押されていない
==========================================================*/
bool KeyTracker::PushKey(eUseKey key)
{
	switch (key)
	{
		case eUseKey::ENTER:
		{
			if (mTracker.pressed.Enter)
			{
				return true;
			}

			break;
		}
		case eUseKey::SPACE:
		{
			if (mTracker.pressed.Space)
			{
				return true;
			}
			break;
		}
		case eUseKey::UP:
		{
			if (mTracker.pressed.Up)
			{
				return true;
			}
			break;
		}
		case eUseKey::DOWN:
		{
			if (mTracker.pressed.Down)
			{
				return true;
			}
			break;
		}
		case eUseKey::LEFT:
		{
			if (mTracker.pressed.Left)
			{
				return true;
			}
			break;
		}
		case eUseKey::RIGHT:
		{
			if (mTracker.pressed.Right)
			{
				return true;
			}
			break;
		}
		case eUseKey::P:
		{
			if (mTracker.pressed.P)
			{
				return true;
			}
			break;
		}
		case eUseKey::R:
		{
			if (mTracker.pressed.R)
			{
				return true;
			}
			break;
		}
		case eUseKey::DEBUG_R:
		{
			if (mTracker.pressed.T)
			{
				return true;
			}
			break;
		}
		//単発押ししないキーが来た場合は処理を行わない
		default:
		{
			break;
		}
	}

	return false;
}

/*==========================================================
キー操作(ベースとなる関数)(長押し処理)
引数：入力するキー
返り値：true→押している	false→押されていない
==========================================================*/
bool KeyTracker::PressKey(eUseKey key)
{
	// キー入力情報を取得する
	auto keyState = DirectX::Keyboard::Get().GetState();
	switch (key)
	{
		case eUseKey::W:
		{
			if (keyState.W)
			{
				return true;
			}
			break;
		}
		case eUseKey::A:
		{
			if (keyState.A)
			{
				return true;
			}
			break;
		}
		case eUseKey::S:
		{
			if (keyState.S)
			{
				return true;
			}
			break;
		}
		case eUseKey::D:
		{
			if (keyState.D)
			{
				return true;
			}
			break;
		}
		case eUseKey::SPACE:
		{
			if (keyState.Space)
			{
				return true;
			}
			break;
		}
		case eUseKey::LEFT:
		{
			if (keyState.Left)
			{
				return true;
			}
			break;
		}
		case eUseKey::RIGHT:
		{
			if (keyState.Right)
			{
				return true;
			}
			break;
		}
		case eUseKey::DEBUG_G:
		{
			if (keyState.G)
			{
				return true;
			}
			break;
		}
		//長押ししないキーが来た場合は処理を行わない
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
void KeyTracker::KeyUpdate()
{
	// キー入力情報を取得する
	auto keyState = mKeybord.get()->GetState();
	mTracker.Update(keyState);

	//強制終了処理
	this->ForcedTermination();
}


/*==========================================================
実行終了処理
引数：なし
返り値：なし
==========================================================*/
void KeyTracker::ForcedTermination()
{
	// キー入力情報を取得する
	auto keyState = DirectX::Keyboard::Get().GetState();
	//もしESCキーが押されたら
	if (keyState.Escape)
	{
		//強制終了する
		PostQuitMessage(0);
	}
}
