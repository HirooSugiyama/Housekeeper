/*
ひとつのフェーズの始まりのテクスチャを管理するクラス
作成者：杉山
作成日：2021/09/18
*/
#include"pch.h"

#include"PhaseCursor.h"

//前方宣言
#include"../Common/ObjectTexture.h"


//画像の拡大率
const DirectX::SimpleMath::Vector2 PhaseCursor::PHASECURSOR_TEXTURE_SCALE(1.f,1.f);

/*===================================
コンストラクタ
引数：なし
===================================*/
PhaseCursor::PhaseCursor()
	:
	mpPhaseCursorTexture()
{
	mpPhaseCursorTexture = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
PhaseCursor::~PhaseCursor()
{
}

/*=================================
初期化処理
引数：なし
返り値：なし
===================================*/
void PhaseCursor::Initialize()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__PHASECURSOR));

	//画像を設定する
	mpPhaseCursorTexture->SetTexture(texture);

	//初期化処理
	mpPhaseCursorTexture->Initialize();
	mpPhaseCursorTexture->SetScale(PHASECURSOR_TEXTURE_SCALE);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void PhaseCursor::Update()
{

}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void PhaseCursor::Draw()
{
	mpPhaseCursorTexture->Draw();
}

/*===================================
座標の取得
引数：生成座標
返り値：なし
===================================*/
void PhaseCursor::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	mpPhaseCursorTexture->SetPosition(position);
}




