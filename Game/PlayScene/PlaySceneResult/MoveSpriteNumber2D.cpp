/*
動く文字画像クラス
作成者：杉山
作成日：2021/12/17
*/
#include"pch.h"

#include"MoveSpriteNumber2D.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
MoveSpriteNumber2D::MoveSpriteNumber2D()
	:
	mpCountNumber(),
	mpSpriteNumber2D(),
	mDrawPosition()
{
	mpCountNumber = std::make_unique<CountNumber>();
	mpSpriteNumber2D = std::make_unique<SpriteNumber2D>();
}

/*===================================
デストラクタ
===================================*/
MoveSpriteNumber2D::~MoveSpriteNumber2D()
{
}

/*===================================
初期化処理
引数：	画像パス
		最初の値
		移動速度(秒)
		最大値
返り値：なし
===================================*/
void MoveSpriteNumber2D::Initialize(const int& textureKey,
									const int& firstNum,
									const float& moveSecondSpeed,
									const int& maxNum)
{

	//画像クラスの初期化処理
	mpSpriteNumber2D->SetTextureKey(textureKey);
	mpSpriteNumber2D->Initialize();

	//移動処理の初期化処理
	mpCountNumber->Initialize(firstNum, moveSecondSpeed, maxNum);
}

/*=================================
更新処理
引数：タイマー
返り値：現在の値
===================================*/
int MoveSpriteNumber2D::Update(const DX::StepTimer& timer)
{
	mpCountNumber->Update(timer);

	return mpCountNumber->GetMoveNum();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void MoveSpriteNumber2D::Draw()
{
	//画像描画
	mpSpriteNumber2D->Create(mpCountNumber->GetMoveNum(), mDrawPosition);
	mpSpriteNumber2D->Draw();
}
