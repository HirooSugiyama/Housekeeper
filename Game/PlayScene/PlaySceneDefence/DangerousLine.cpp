/*
警告線クラス
作成者：杉山
作成日：2021/10/06
*/
#include"pch.h"

#include"DangerousLine.h"

//定数
//座標
const DirectX::SimpleMath::Vector3 DangerousLine::ASSETLINE_MODEL_POSITION(0.f, 0.75f, -5.f);
//拡大率							
const DirectX::SimpleMath::Vector3 DangerousLine::ASSETLINE_MODEL_SCALE(20.f, 3.f, 0.05f);

/*===================================
コンストラクタ
引数：なし
===================================*/
DangerousLine::DangerousLine()
	:
	mpAssertLineModel()
{
	mpAssertLineModel = std::make_unique<ObjectModel>();
}

/*===================================
デストラクタ
===================================*/
DangerousLine::~DangerousLine()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void DangerousLine::Initialize()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__ASSERTLINEMODEL));
	mpAssertLineModel->SetModel(model);
	mpAssertLineModel->SetPosition(ASSETLINE_MODEL_POSITION);
	mpAssertLineModel->SetScale(ASSETLINE_MODEL_SCALE);
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void DangerousLine::Draw()
{
	//モデル描画処理
	mpAssertLineModel->Draw();
}

/*============================================================
Z座標の取得(エフェクト発動基準座標)(関数の都合上CPPで処理)
引数：なし
返り値：モデルのZ座標
============================================================*/
float DangerousLine::GetLinePositionZ()const
{
	float returnpos = mpAssertLineModel->GetPosition().z;

	return returnpos;
}




