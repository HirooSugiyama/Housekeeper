/*
所持金周りの描画画像管理クラス
作成者：杉山
作成日：2021/10/21
*/

#include"pch.h"
#include"MoneyTexture.h"

//現在の所持金の取得
#include"Game/Money/Money.h"
//画像の座標
const DirectX::SimpleMath::Vector2 MoneyTexture::UI_MONEYTEXTURE_POSITION(1000.f,0.f);

//画像の拡大率
const DirectX::SimpleMath::Vector2 MoneyTexture::UI_MONEYTEXTURE_SCALE(1.3f,1.3f);

//実際の値の描画
const DirectX::SimpleMath::Vector2 MoneyTexture::UI_MONEY_NUM_POSITION =
	UI_MONEYTEXTURE_POSITION + DirectX::SimpleMath::Vector2(230, 8.f);

/*===================================
コンストラクタ
引数：なし
===================================*/
MoneyTexture::MoneyTexture()
	:
	mpTexture(),
	mpSpriteTexture(nullptr)
{
	mpTexture = std::make_unique<ObjectTexture>();
	mpSpriteTexture = std::make_unique<SpriteNumber2D>();
}

/*===================================
デストラクタ
===================================*/
MoneyTexture::~MoneyTexture()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void MoneyTexture::Initialize()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto model=pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__MONEYGAUGE));

	//画像の設定
	mpTexture->SetTexture(model);
	mpTexture->Initialize();

	//座標の設定
	mpTexture->SetPosition(UI_MONEYTEXTURE_POSITION);

	//拡大率の設定
	mpTexture->SetScale(UI_MONEYTEXTURE_SCALE);

	//数字画像の初期化処理
	mpSpriteTexture->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING));
	mpSpriteTexture->Initialize();
}


/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void MoneyTexture::Draw()
{
	//画像の描画
	mpTexture->Draw();

	//所持金の描画
	auto& pM = Money::GetMoneyInstance();

	mpSpriteTexture->Create(pM.GetMoney(), UI_MONEY_NUM_POSITION);
	mpSpriteTexture->Draw();
}
