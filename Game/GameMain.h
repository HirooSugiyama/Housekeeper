/*
ゲームメイン
作成者：杉山
作成日：2021/10/21
*/
#pragma once

#include "StepTimer.h"



// シーンの列挙
enum class eGameScene : int
{
    NONE,

    TITLE,
    STAGE_SELECT,
    PLAY,

};

// 前方宣言
class DebugCamera;
class ObjectTexture;

class IScene;

/// <summary>
/// Gameクラスから、ユーザ処理部分を抜き出したクラス
/// </summary>
class GameMain
{
private:
    //定数
    //1台目のコントローラー
    static const int GAMEPAD_ONE = 0;
    //ゲームパッドアイコン
    //座標
    static const DirectX::SimpleMath::Vector2 GAMEPAD_ICON_POSITION;
    //拡大率
    static const DirectX::SimpleMath::Vector2 GAMEPAD_ICON_SCALE;

    //変数

	// 次のシーン番号
	eGameScene mNextScene;

	// シーン
	std::unique_ptr<IScene> mpScene;




public:
    GameMain();
    ~GameMain();

    void Initialize();
    void Update(const DX::StepTimer& timer);
    void Render();
    void Finalize();

	// シーン関係処理
private:
	// シーンの作成
	void CreateScene();

	// シーンの削除
	void DeleteScene();

    //キーボードの更新処理
    void KeyboardUpdate();

    //ゲームパッドの更新処理
    void GamePadUpdate();
};
