/*
赤色点滅テクスチャ管理クラス
作成者：杉山
作成日：2021/10/07
*/
#include"pch.h"

#include"RedAssert.h"


//座標
const DirectX::SimpleMath::Vector2 RedAssert::DANGEROUSUI_TEXTURE_POSITION(0.f,0.f);
//拡大率
const DirectX::SimpleMath::Vector2 RedAssert::DANGEROUSUI_TEXTURE_SCALE(1.f,1.f);

//透明度増幅
const float RedAssert::DANGEROUSUI_SIN_NUM = 3.5f;
//透明度の値調節
const float RedAssert::DANGEROUSUI_SIN_SHIFT = 0.45f;

/*===================================
コンストラクタ
引数：なし
===================================*/
RedAssert::RedAssert()
	:
	mpDangerousUI(),
	mSin(0.f),
	mPassFlag(false)
{
	mpDangerousUI = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
RedAssert::~RedAssert()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void RedAssert::Initialize()
{
	auto pRM = ResourceManager::GetInstance();
	auto texture=pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__RED));

	//画像の初期化
	mpDangerousUI->SetTexture(texture);
	mpDangerousUI->Initialize();
	mpDangerousUI->SetPosition(DANGEROUSUI_TEXTURE_POSITION);
	mpDangerousUI->SetScale(DANGEROUSUI_TEXTURE_SCALE);
	mpDangerousUI->SetAlpha(0.f);	//最初は透明で保存しておく
}

/*=================================
更新処理
引数：なし
返り値：なし
===================================*/
void RedAssert::Update()
{
	//フラグが立っていたら通す
	if (mPassFlag)
	{
		//値を取得
		float sinf = std::sinf(DirectX::XMConvertToRadians(mSin));

		//α値として使用する
		mpDangerousUI->SetAlpha(sinf - DANGEROUSUI_SIN_SHIFT);

		//値を更新する
		mSin += DANGEROUSUI_SIN_NUM;
	}
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void RedAssert::Draw()
{
	//フラグが立っていたら通す
	if (mPassFlag)
	{
		mpDangerousUI->Draw();
	}	
}




