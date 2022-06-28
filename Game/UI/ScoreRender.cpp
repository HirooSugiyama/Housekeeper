/*
スコア周りの描画クラス
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"

#include"ScoreRender.h"

//スコアの描画位置
const DirectX::SimpleMath::Vector2 ScoreRender::SCORE_NUM_POSITION(270.f, 0.f);

//スコアの文字画像の描画位置
const DirectX::SimpleMath::Vector2 ScoreRender::SCORE_STRING_POSITION(20.f, 10.f);

//スコアの拡大率
const float ScoreRender::SCORE_NUM_SCALE = 1.5f;

//スコア文字の拡大率
const float ScoreRender::SCORE_STRING_SCALE = 1.5f;

/*===================================
コンストラクタ
引数：なし
===================================*/
ScoreRender::ScoreRender()
	: 
	mpDrawScore(),
	mpScoreStringTexture()
{
	mpDrawScore = std::make_unique<SpriteNumber2D>();
	mpScoreStringTexture = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
ScoreRender::~ScoreRender()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void ScoreRender::Initialize()
{
	//スコアのフォントを指定
	mpDrawScore->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWNORMALSTRING));
	mpDrawScore->Initialize();
	mpDrawScore->SetAlign(eAlign::LEFT);
	mpDrawScore->SetScale(SCORE_NUM_SCALE);

	//リソースの取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SCORE));

	//スコア文字の初期化処理
	mpScoreStringTexture->SetTexture(texture);
	mpScoreStringTexture->Initialize();
	mpScoreStringTexture->SetPosition(SCORE_STRING_POSITION);
	mpScoreStringTexture->SetScale(DirectX::SimpleMath::Vector2(SCORE_STRING_SCALE, SCORE_STRING_SCALE));
}

/*===================================
描画処理
引数：スコア値
返り値：なし
===================================*/
void ScoreRender::Draw(int scoreNum)
{
	//スコアの描画
	mpScoreStringTexture->Draw();

	mpDrawScore->Create(scoreNum, SCORE_NUM_POSITION);
	mpDrawScore->Draw();
}
