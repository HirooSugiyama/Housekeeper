/*
ステージ選択タグ
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"
#include"StageNumberTag.h"

//画像拡大率
const DirectX::SimpleMath::Vector2 StageNumberTag::TEX_SCALE(0.85f,1.1f);

//画像描画位置から数字描画位置を算出するための定数
const DirectX::SimpleMath::Vector2 StageNumberTag::NUM_SHIFT(225.f,-5.f);

/*=================================
コンストラクタ
引数：なし
===================================*/
StageNumberTag::StageNumberTag()
	:
	mpBackGround(nullptr),
	mDrawStageString(),
	mDrawPosition()
{
	mpBackGround = std::make_unique<ObjectTexture>();
	mpStageSpriteNum = std::make_unique<SpriteNumber2D>();
}

/*===================================
デストラクタ
===================================*/
StageNumberTag::~StageNumberTag()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void StageNumberTag::Initialize()
{
	//初期化処理
	mpBackGround->Initialize();

	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGESCALE));

	//画像の設定
	mpBackGround->SetTexture(texture);
	//拡大率の設定
	mpBackGround->SetScale(TEX_SCALE);



	//スコアのフォントを指定
	mpStageSpriteNum->SetTextureKey(static_cast<int>(StageSelectTexturesResouce::TEXTURE__STAGENUMBERFONT));
	mpStageSpriteNum->Initialize();
	mpStageSpriteNum->SetAlign(eAlign::LEFT);
	mpStageSpriteNum->SetScale(Utility::STRING_SIZE_SMALL);

}

/*===================================
描画処理
引数：描画フラグ(false 描画しない)
返り値：なし
===================================*/
void StageNumberTag::Draw(const bool& flag)
{
	//例外数字なら処理を行わない
	if (mDrawStageString == Utility::EXCEPTION_NUM)
	{
		return;
	}
	if (!flag)
	{
		return;
	}

	//背景の描画
	mpBackGround->Draw();

	//数字の描画
	mpStageSpriteNum->Create(mDrawStageString, mDrawPosition + NUM_SHIFT);
	mpStageSpriteNum->Draw();
}

/*===================================
描画位置の指定
引数：座標
返り値：なし
===================================*/
void StageNumberTag::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	mDrawPosition = position;
	mpBackGround->SetPosition(position);
}




