/*
タイトルシーン
作成者：杉山
作成日：2021/10/21
*/
#pragma once

#include "../IScene.h"
#include "Game/GameMain.h"

//所持
#include"Game/Common/Cloud.h"
#include"Game/Common/ObjectSpriteTexture.h"

class TitleScene : public IScene
{
private:

	//タイトルバー初期切り取り位置
	static const RECT TITLE_BAR_INIT_RECT;

	//ロゴの座標
	static const DirectX::SimpleMath::Vector2 TITLE_LOGO_POSITION;
	//開始ボタン位置
	static const DirectX::SimpleMath::Vector2 TITLE_START_BAR_POSITION;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpLogo;

	std::unique_ptr<Cloud> mpCloud;

	std::unique_ptr<ObjectSpriteTexture> mpTitleBar;

	//音楽ID
	int mBGMID;

public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	// 初期化
	void Initialize() override;

	// 更新
	eGameScene Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

private:
	//ゲームパッドとキーを切り替え
	void ChangeControl();

	//BGMを流す
	void PlayBGM()override;

	//BGMを止める
	void StopBGM()override;
};