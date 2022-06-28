/*
準備フェーズ(昼)と防衛フェーズ(夜)のUIを管理するクラス
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"
#include "TimeOfDay.h"

//前方宣言
//ポインタの保存
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"

//定数
//進む距離
const float TimeOfDay::UI_TOD_ICON_DISTANCE = 1050.f;

//ゲージの拡大率
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_GAUGE_SCALE(2.f, 2.2f);

//アイコンの拡大率
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_ICON_SCALE(0.8f, 0.8f);

//ゲージの座標
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_GAUGE_POSITION(120.f, 710.f);

//アイコンの初期座標
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_ICON_POSITION(100.f, 700.f);

//フレーム換算
const float TimeOfDay::CAST_TO_FRAME_TO_SECOND = 60.f;

/*======================
コンストラクタ
========================*/
TimeOfDay::TimeOfDay()
	:
	mpTODGauge(),
	mpTODIcon(),
	mpTimer(),
	mIconMoveVelocity()
{
	mpTODGauge = std::make_unique<ObjectTexture>();
	mpTODIcon = std::make_unique<ObjectTexture>();
}

/*======================
デストラクタ
========================*/
TimeOfDay::~TimeOfDay()
{
}

/*================================================
初期化処理
引数：タイマーのポインタ、現在のフェーズのポインタ
================================================*/
void TimeOfDay::Initialize(Timer* pTimer, const int& maxPhaseNum)
{

	mpTimer = pTimer;

	//画像の設定
	this->SetTexture();
	//座標の設定
	this->SetPosition();
	//拡大率の設定
	this->SetScale();

	mpTODGauge->Initialize();
	mpTODIcon->Initialize();


	mMaxGameTime = mpTimer->GetMaxTime() * maxPhaseNum;


	//毎フレームの速度を算出
	mIconMoveVelocity = this->CalculationIconVelocity();
}

/*========================
更新処理
========================*/
void TimeOfDay::Update()
{
	//現在の座標保存用変数
	DirectX::SimpleMath::Vector2 position= DirectX::SimpleMath::Vector2::Zero;

	position = mpTODIcon->GetPosition() + DirectX::SimpleMath::Vector2(mIconMoveVelocity, 0.f);

	mpTODIcon->SetPosition(position);
}

/*========================
描画処理
========================*/
void TimeOfDay::Draw()
{
	//下地の画像を描画
	mpTODGauge->Draw();
	mpTODIcon->Draw();
}

/*========================
画像の設定:private
========================*/
void TimeOfDay::SetTexture()
{
	auto pRM = ResourceManager::GetInstance();

	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__FAZEGAUGE));
	mpTODGauge->SetTexture(texture);

	texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__MOONICON));
	mpTODIcon->SetTexture(texture);
}

/*=======================
座標の設定:private
========================*/
void TimeOfDay::SetPosition()
{
	//ゲージの座標設定
	mpTODGauge->SetPosition(UI_TOD_GAUGE_POSITION);
	mpTODIcon->SetPosition(UI_TOD_ICON_POSITION);
}

/*========================
拡大率の設定:private
========================*/
void TimeOfDay::SetScale()
{
	mpTODGauge->SetScale(UI_TOD_GAUGE_SCALE);
	mpTODIcon->SetScale(UI_TOD_ICON_SCALE);
}

/*==================================
アイコンが進むスピードを算出:private
引数：フェーズの時間
返り値：実際に毎フレーム動く距離
==================================*/
float TimeOfDay::CalculationIconVelocity()
{
	//返り値変数宣言
	float velnum=0;

	//進む距離/Phaseの時間=進むスピード(1秒当たり)
	velnum = UI_TOD_ICON_DISTANCE / mMaxGameTime;
	
	//1秒当たりの進むスピードなので、フレーム換算する。
	velnum /= CAST_TO_FRAME_TO_SECOND;


	return velnum;
}
