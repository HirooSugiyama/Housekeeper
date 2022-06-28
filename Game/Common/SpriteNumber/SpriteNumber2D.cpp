/*
スプライトシートの数字を２D描画するクラス
作成者：杉山
作成日：2021/12/11
*/
#include"pch.h"

#include"SpriteNumber2D.h"

//数字1枚当たりの画像サイズ
const RECT SpriteNumber2D::SPRITE_SIZE = { 0,0,160,320 };

//画像の拡大率
const DirectX::SimpleMath::Vector2 SpriteNumber2D::TEX_SCALE(0.15f, 0.15f);

//文字間
const int SpriteNumber2D::STRING_SPACE = 200;

/*===================================
コンストラクタ
引数：なし
===================================*/
SpriteNumber2D::SpriteNumber2D()
	:
	NumberBase(),
	mpNumberTexture{},
	mUseFlag{},
	mInitPosition(),
	mAlign(eAlign::RIGHT),
	mNumShift(TEX_SCALE.x * STRING_SPACE),
	mTextureScale(TEX_SCALE)
{
	//画像の準備
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i] = std::make_unique<ObjectSpriteTexture>
			(
				SPRITE_SIZE,						//画像サイズ(切り取り後)
				DirectX::SimpleMath::Vector2::Zero,	//座標
				TEX_SCALE							//拡大率
			);
	}
}

/*===================================
デストラクタ
===================================*/
SpriteNumber2D::~SpriteNumber2D()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void SpriteNumber2D::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(NumberBase::GetTextureKey());

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetTexture(texture);

		mpNumberTexture[i]->Initialize();
		mpNumberTexture[i]->SetRect(SPRITE_SIZE);
	}
}

/*==================================
作成処理
引数：表示する数字、表示する座標
返り値：なし
===================================*/
void SpriteNumber2D::Create(const int& num, const DirectX::SimpleMath::Vector2& position)
{
	//座標設定
	mInitPosition = position;

	//各種数字を保存する//必要な数字を選び出す
	this->CreateNumber(this->ChooseNum(num));

	//文字間生成処理
	this->CreateStringShift();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void SpriteNumber2D::Draw()
{

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//例外数字以外なら描画する
		if (mUseFlag[i])
		{
			mpNumberTexture[i]->Draw();
		}		
	}
}

/*===============================================
拡大率を設定する
引数：拡大率
返り値：なし
=================================================*/
void SpriteNumber2D::SetScale(float scale)
{
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mTextureScale = TEX_SCALE * DirectX::SimpleMath::Vector2(scale, scale);
		mNumShift = mTextureScale.x * STRING_SPACE;
		mpNumberTexture[i]->SetScale(mTextureScale);

		//文字間を生成しなおす
		this->CreateStringShift();
	}
}

/*===============================================
各変数にほしい番号を入れる:private
引数：作成する数字群
返り値：なし
=================================================*/
void SpriteNumber2D::CreateNumber(const std::vector<int>& num)
{
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//未使用処理
		mUseFlag[i] = false;
		mpNumberTexture[i]->SetRect(SPRITE_SIZE);
	}

	//数字設定
	for (int i = 0; i < static_cast<int>(num.size()); i++)
	{
		if (mUseFlag[i])continue;

		mpNumberTexture[i]->Beside(static_cast<float>(SPRITE_SIZE.right), num[i]);
		mUseFlag[i] = true;
	}
}

/*===============================================
文字間生成処理:private
引数：なし
返り値：なし
=================================================*/
void SpriteNumber2D::CreateStringShift()
{
	//使用する桁に合わせて一番右の座標を設定する
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		if (mUseFlag[i])
		{
			switch (mAlign)
			{
				case eAlign::LEFT:
				{
					mInitPosition.x += mNumShift;
					break;
				}
				case eAlign::RIGHT:
				{
					mInitPosition.x -= mNumShift;
					break;
				}
			}
		}
	}


	//座標を設定する

	switch (mAlign)
	{
		case eAlign::LEFT:
		{
			for (int i = MAX_DIGIT_NUM - 1; i >= 0; i--)
			{
				if (mUseFlag[i])
				{
					mInitPosition.x -= mNumShift;
					mpNumberTexture[i]->SetPosition(mInitPosition);
				}
			}
			break;
		}
		case eAlign::RIGHT:
		{
			for (int i = 0; i < MAX_DIGIT_NUM; i++)
			{
				if (mUseFlag[i])
				{
					mInitPosition.x += mNumShift;
					mpNumberTexture[i]->SetPosition(mInitPosition);
				}
			}
			break;
		}
	}
}
