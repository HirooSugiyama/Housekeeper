/*
キーボードトラッカーの取得(シングルトン)
作成者：杉山
作成日：2021/10/21
キー入力は極力数を増やしたくないので、敢えて追加しにくい形で作成しています。
*/
#pragma once

#include<Keyboard.h>

class KeyTracker
{
public:
	//自分自身の取得
	static KeyTracker* GetKeyTrackerInstance()
	{
		static KeyTracker kt;

		return &kt;
	}

private:

	//使用するキー一覧
	enum class eUseKey
	{
		ENTER,			//各種決定
		W, A, S, D,		//移動
		SPACE,			//行動
		UP, DOWN,		//行動切り替え
		LEFT, RIGHT,	//武器切り替え
		P,				//Pause
		R,				//リスタート

		DEBUG_G,	//デバッグ処理
		DEBUG_R,	//デバッグ処理
	};


	//トラッカー
	DirectX::Keyboard::KeyboardStateTracker mTracker;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> mKeybord;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	KeyTracker(const KeyTracker& kt) = delete;
	KeyTracker operator=(const KeyTracker& kt) = delete;

	//コンストラクタ
	KeyTracker();
	//デストラクタ
	~KeyTracker() = default;

	//キー操作(ベースとなる関数)
	bool PushKey(eUseKey key);
	bool PressKey(eUseKey key);

public:
	//更新処理
	void KeyUpdate();

	//使用用途の数だけ関数を作成する

	//決定
	bool Decision() { return this->PushKey(eUseKey::ENTER); }

	//下へ
	bool SelectUnder() { return this->PushKey(eUseKey::DOWN); }

	//上へ
	bool SelectOver() { return this->PushKey(eUseKey::UP); }

	//歩行
	bool WalkForward() { return this->PressKey(eUseKey::W); }
	bool WalkBack() { return this->PressKey(eUseKey::S); }
	bool WalkLeft() { return this->PressKey(eUseKey::A); }
	bool WalkRight() { return this->PressKey(eUseKey::D); }

	bool Walk()
	{
		return this->WalkForward() || this->WalkBack() || this->WalkLeft() || this->WalkRight();
	}

	//強攻撃
	bool PushActionStrongAttack() { return this->PushKey(eUseKey::SPACE); }
	bool PressActionStrongAttack() { return this->PressKey(eUseKey::SPACE); }

	//弱攻撃
	bool ActionWeekAttack() { return this->PushKey(eUseKey::SPACE); }
	//壁を建てる
	bool ActionDefenseHouse() { return this->PressKey(eUseKey::SPACE); }

	//武器切り替え
	//攻撃状態を切り替え
	bool SwitchToWeapon()
	{
		return this->PushKey(eUseKey::LEFT) || this->PushKey(eUseKey::RIGHT);
	}

	//行動状態切り替え
	//攻撃状態に変更
	bool ChangeActionLeft() { return this->PushKey(eUseKey::LEFT); }
	//防御状態に切り替え
	bool ChangeActionRight() { return this->PushKey(eUseKey::RIGHT); }

	//スキップ
	bool Skip(bool pauseFlag)
	{
		//ポーズ解放時は処理しない
		if (pauseFlag)return false;

		return this->PushKey(eUseKey::ENTER);
	}

	//戻る
	bool Back() { return this->PushKey(eUseKey::LEFT); }

	//左回転
	bool LeftRotation() { return this->PressKey(eUseKey::LEFT); }

	//右回転
	bool RightRotation() { return this->PressKey(eUseKey::RIGHT); }

	//カメラ切り替え処理
	bool ChangeCamera() { return this->PushKey(eUseKey::ENTER); }

	//Debug処理
	bool DEBUGPRESS() { return this->PressKey(eUseKey::DEBUG_G); }
	bool DEBUGPUSH() { return this->PushKey(eUseKey::DEBUG_R); }

	//ポーズ
	bool Pause() { return this->PushKey(eUseKey::P); }

	//リスタート
	bool ReStart() { return this->PushKey(eUseKey::R); }

private:

	//実行終了処理
	void ForcedTermination();
};