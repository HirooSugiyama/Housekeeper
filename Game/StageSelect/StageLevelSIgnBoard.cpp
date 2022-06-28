/*
ステージレベルの看板
作成者：杉山
作成日：2022/03/12
*/
#include"pch.h"
#include"StageLevelSignBoard.h"


//画像の拡大率
const DirectX::SimpleMath::Vector2 StageLevelSignBoard::TEXTURE_SCALE(1.f,0.80f);
//画像の座標
const DirectX::SimpleMath::Vector2 StageLevelSignBoard::TEXTURE_POSITON(640.f,435.f);

/*===================================
コンストラクタ
===================================*/
StageLevelSignBoard::StageLevelSignBoard()
	:mpSignBoard()
{
	mpSignBoard = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
StageLevelSignBoard::~StageLevelSignBoard()
{
}

/*===================================
初期化処理
===================================*/
void StageLevelSignBoard::Initialize()
{
	//初期設定
	mpSignBoard->Initialize();
	//画像の設定
	const auto pResouceManager = ResourceManager::GetInstance();
	const auto texture = pResouceManager->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__SIGNBOARD));
	mpSignBoard->SetTexture(texture);

	//座標設定
	mpSignBoard->SetPosition(TEXTURE_POSITON);
	//拡大率設定
	mpSignBoard->SetScale(TEXTURE_SCALE);
}

/*===================================
描画処理
===================================*/
void StageLevelSignBoard::Draw()
{
	mpSignBoard->Draw();
}