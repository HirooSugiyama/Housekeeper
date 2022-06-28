/*
残りフェーズを計測する画像を管理するクラス
*/
#include"pch.h"
#include"PhaseCount.h"

//前方宣言
//所持
#include"../Common/ObjectTexture.h"
#include "Game/Manager/ResourceManager.h"


//debug
#include"Game/Interface/DirectXTKInterface/DirectXTKInterface.h"
#include<SpriteFont.h>

using namespace DirectX::SimpleMath;


//座標
const DirectX::SimpleMath::Vector2
	PhaseCount::UI_PHAZECOUNT_POS = Vector2(0.f, 150.f);
//拡大率
const DirectX::SimpleMath::Vector2
	PhaseCount::UI_PHAZECOUNT_SCALE = Vector2(1.f, 1.f);


/*==============
コンストラクタ
==============*/
PhaseCount::PhaseCount()
	:mpPhaseCountGroundwork()
	, mpPhaseNum(0)
{
	mpPhaseCountGroundwork = std::make_unique<ObjectTexture>();
}

/*==============
デストラクタ
==============*/
PhaseCount::~PhaseCount()
{
}

/*============================
初期化処理
引数：フェーズ数のポインタ
============================*/
void PhaseCount::Initialize(int* pPhaseCountNum)
{
	//ポインタの保存
	mpPhaseNum = pPhaseCountNum;

	//1種類しかないためすべてここで行う
	//リソースマネージャーの取得
	auto pRM = ResourceManager::GetInstance();

	//画像の設定
	auto texture = pRM->GetTexture("WoodMat");
	mpPhaseCountGroundwork->SetTexture(texture);
	//座標の設定
	mpPhaseCountGroundwork->SetPos(UI_PHAZECOUNT_POS);
	//拡大率の設定
	mpPhaseCountGroundwork->SetScale(UI_PHAZECOUNT_SCALE);

	mpPhaseCountGroundwork->Initialize();
}

/*==============
描画処理
==============*/
void PhaseCount::Draw()
{
	//mpPhaseCountGroundwork->Draw();

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

	wchar_t buf[32];
	swprintf_s(buf, 32, L"Phase = %d", *mpPhaseNum);
	//描画開始
	pDxIF.GetSpriteFont()->DrawString
	(pDxIF.GetSpriteBatch(), buf, DirectX::XMFLOAT2(UI_PHAZECOUNT_POS)); 


}
