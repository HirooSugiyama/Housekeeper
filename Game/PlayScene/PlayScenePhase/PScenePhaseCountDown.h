/*
カウントダウンフェーズ
作成者：杉山
作成日：2021/09/30
*/
#pragma once

//基底クラス
#include"PlayScenePhaseBase.h"

//所持
#include"../../Common/SpriteNumber/SpriteNumber2D.h"
#include"../PlaySceneCommon/Administrator/Timer.h"

class PScenePhaseCountDown :public PlayScenePhaseBase
{
private:

	//カウントダウン時間
	static const int CountDown_MAX_NUM;

	//画面中央値
	static const DirectX::SimpleMath::Vector2 WINDOW_CENTER;


	//PlaySceneオブジェクトへ保存用のポインタ
	PlayScene* mpPlayScene;

	//カウントダウン用タイマー
	std::unique_ptr<Timer> mpCountDownTimer;

	std::unique_ptr<SpriteNumber2D> mpCountDownString;


public:
	//コンストラクタ
	PScenePhaseCountDown();

	//デストラクタ
	~PScenePhaseCountDown();
	
	//初期化
	void Initialize(PlayScene* pPlayScene)override;

	//更新
	void Update()override;

	//描画
	void Draw()override;

	//State変更前のリセット処理
	void Reset()override;
};