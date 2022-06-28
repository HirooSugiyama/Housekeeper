/*
地面のクラス
作成者：杉山
作成日：2021/06/28
*/
#include"pch.h"
#include "Ground.h"

//定数
//地面の中心座標
const DirectX::SimpleMath::Vector3 Ground::GROUND_POSITION(0.f,0.5f,-15.f);
//地面の拡大率
const DirectX::SimpleMath::Vector3 Ground::GROUND_SCALE(40.f, 0.5f, 60.f);


/*===================================
コンストラクタ
引数：なし
===================================*/
Ground::Ground()
	:
	mpGroundModel()
{
	//生成
	mpGroundModel = std::make_unique<ObjectModel>();
}

/*===================================
デストラクタ
===================================*/
Ground::~Ground()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void Ground::Initialize()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__STAGE));
	mpGroundModel->SetModel(model);
	mpGroundModel->SetPosition(GROUND_POSITION);
	mpGroundModel->SetScale(GROUND_SCALE);
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void Ground::Draw()
{
	mpGroundModel->Draw();
}
