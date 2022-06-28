/*
ステージのレベル描画クラス
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"
#include"StageLevel.h"



//画像初期座標
const DirectX::SimpleMath::Vector2 StageLevel::STAGELEVELOCITY_TEXTURE_INIT_POSITION(855.f, 615.f);

//画像拡大率
const DirectX::SimpleMath::Vector2 StageLevel::STAGELEVELOCITY_TEXTURE_SCALE(1.2f,1.2f);

//画像をずらす幅
const float StageLevel::STAGELEVELOCITY_SHIFT_POSITION_X = 50.f;


/*===================================
コンストラクタ
引数：なし
===================================*/
StageLevel::StageLevel()
	:mpStarTexture()
{
	for (int i = 0; i < STAGE_MAX_LEVELOCITY; i++)
	{
		mpStarTexture[i] = std::make_unique<ObjectTexture>();
	}
}

/*===================================
デストラクタ
===================================*/
StageLevel::~StageLevel()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void StageLevel::Initialize()
{
	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAR));

	for (int i = 0; i < STAGE_MAX_LEVELOCITY; i++)
	{
		//画像設定
		mpStarTexture[i]->SetTexture(textute);

		//初期化処理
		mpStarTexture[i]->Initialize();

		//座標設定
		DirectX::SimpleMath::Vector2 position =
			STAGELEVELOCITY_TEXTURE_INIT_POSITION +
			DirectX::SimpleMath::Vector2(i * STAGELEVELOCITY_SHIFT_POSITION_X, 0.f);

		mpStarTexture[i]->SetPosition(position);

		//拡大率設定
		mpStarTexture[i]->SetScale(STAGELEVELOCITY_TEXTURE_SCALE);
	}
}

/*===================================
描画処理
引数：ステージレベル
返り値：なし
===================================*/
void StageLevel::Draw(const int& stagelevel)
{
	for (int i = 0; i<stagelevel; i++)
	{
		mpStarTexture[i]->Draw();
	}
}
