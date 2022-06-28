/*
準備フェーズ(昼)と防衛フェーズ(夜)のUIを管理するクラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once

//所持
#include"../Common/ObjectTexture.h"

//前方宣言
class Timer;

class TimeOfDay
{
private:

	//定数
	//進む距離 
	static const float UI_TOD_ICON_DISTANCE;

	//ゲージの拡大率
	static const DirectX::SimpleMath::Vector2 UI_TOD_GAUGE_SCALE;

	//アイコンの拡大率
	static const DirectX::SimpleMath::Vector2 UI_TOD_ICON_SCALE;

	//ゲージの座標
	static const DirectX::SimpleMath::Vector2 UI_TOD_GAUGE_POSITION;

	//アイコンの初期座標
	static const DirectX::SimpleMath::Vector2 UI_TOD_ICON_POSITION;

	//フレーム換算
	static const float CAST_TO_FRAME_TO_SECOND;

	//変数
	//ゲージの画像
	std::unique_ptr<ObjectTexture> mpTODGauge;
	//アイコンの画像
	std::unique_ptr<ObjectTexture> mpTODIcon;

	//ゲームの最大時間
	int mMaxGameTime;
	
	//保存用変数
	Timer* mpTimer;

	//アイコンの進む速度
	float mIconMoveVelocity;


public:
	//コンストラクタ
	TimeOfDay();
	//デストラクタ
	~TimeOfDay();

	//初期化
	void Initialize(Timer* pTimer,const int& maxPhaseNum);
	//更新
	void Update();
	//描画
	void Draw();
	//アイコンの開始点を取得
	DirectX::SimpleMath::Vector2 GetIconStartPosition()const { return UI_TOD_ICON_POSITION; }
	//アイコンの最終点を取得
	float GetIconDistancePosition() const { return UI_TOD_ICON_DISTANCE; }

private:

	//画像の設定
	void SetTexture();
	//座標の設定
	void SetPosition();
	//拡大率の設定
	void SetScale();

	//アイコンが進むスピードを算出
	float CalculationIconVelocity();


};
