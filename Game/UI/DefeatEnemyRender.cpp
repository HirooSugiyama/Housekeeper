/*
現在の敵の数を描画するクラス
作成者：杉山
作成日：2021/12/11
*/
#include"pch.h"

#include"DefeatEnemyRender.h"

//背景画像の座標
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::TEX_POSITION(30.f, 70.f);
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::TEX_SCALE(0.5f,0.5f);

//現在の敵の数の文字画像の座標
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::CURRENT_NUM_POSITION(90.f, 95.f);
const float DefeatEnemyRender::CURRENT_NUM_SCALE = 1.f;

//敵の最大数の画像の座標
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::OVERALL_NUM_POSITION(120.f, 130.f);
const float DefeatEnemyRender::OVERALL_NUM_SCALE = 0.7f;

/*===================================
コンストラクタ
引数：なし
===================================*/
DefeatEnemyRender::DefeatEnemyRender()
	:
	mpDefeatEnemyTexture(),
	mpCurrentEnemyNum(),
	mpOverallEnemyNum()
{
	mpDefeatEnemyTexture = std::make_unique<ObjectTexture>();
	mpCurrentEnemyNum = std::make_unique<SpriteNumber2D>();
	mpOverallEnemyNum = std::make_unique<SpriteNumber2D>();
}

/*===================================
デストラクタ
===================================*/
DefeatEnemyRender::~DefeatEnemyRender()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void DefeatEnemyRender::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__DEFEATENEMY));
	//画像設定処理
	mpDefeatEnemyTexture->SetTexture(texture);

	mpCurrentEnemyNum->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWDAMAGESTRING));
	mpOverallEnemyNum->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWNORMALSTRING));

	//初期化処理
	mpDefeatEnemyTexture->Initialize();
	mpDefeatEnemyTexture->SetPosition(TEX_POSITION);
	mpDefeatEnemyTexture->SetScale(TEX_SCALE);

	mpCurrentEnemyNum->Initialize();
	mpCurrentEnemyNum->SetScale(CURRENT_NUM_SCALE);

	mpOverallEnemyNum->Initialize();
	mpOverallEnemyNum->SetAlign(eAlign::LEFT);
	mpOverallEnemyNum->SetScale(OVERALL_NUM_SCALE);
}

/*===================================
描画処理
引数：現在の敵の数、敵の最大数
返り値：なし
===================================*/
void DefeatEnemyRender::Draw(int currentNum, int overallNum)
{
	//初期化処理
	mpDefeatEnemyTexture->Draw();

	mpCurrentEnemyNum->Create(currentNum, CURRENT_NUM_POSITION);
	mpCurrentEnemyNum->Draw();

	mpOverallEnemyNum->Create(overallNum, OVERALL_NUM_POSITION);
	mpOverallEnemyNum->Draw();
}