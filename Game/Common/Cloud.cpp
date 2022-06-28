/*
空に浮く雲を管理するクラス
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"
#include "Cloud.h"

//前方宣言
//所持
#include"../Common/ObjectTexture.h"



	//雲の初期座標
const DirectX::SimpleMath::Vector2 Cloud::CLOUD_POSITION1(20.f, 50.f);
const DirectX::SimpleMath::Vector2 Cloud::CLOUD_POSITION2(400.f, 200.f);
const DirectX::SimpleMath::Vector2 Cloud::CLOUD_POSITION3(700.f, 80.f);


//雲の移動速度
const float Cloud::CLOUD_VELOCITY = 0.5f;
//雲の画面外座標
const float Cloud::CLOUD_OVER_POSITION = 1200.f;
const float Cloud::CLOUD_RESET_POSITION = -200.f;

/*===================
コンストラクタ
引数：なし
===================*/
Cloud::Cloud()
	:
	mpClouds{}
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i] = std::make_unique<ObjectTexture>();
	}	
}

/*===================
デストラクタ
===================*/
Cloud::~Cloud()
{
}

/*===================
初期化処理
引数：ファイルの鍵
返り値：なし
===================*/
void Cloud::Initialize(const int& fileKey)
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->Initialize();
	}

	auto pRM = ResourceManager::GetInstance();
	auto texture=pRM->GetTexture(fileKey);

	//画像をセットする
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->SetTexture(texture);
	}

	//それぞれの座標を設定する
	mpClouds[0]->SetPosition(CLOUD_POSITION1);
	mpClouds[1]->SetPosition(CLOUD_POSITION2);
	mpClouds[2]->SetPosition(CLOUD_POSITION3);
}

/*===================
更新処理
引数：なし
返り値：なし
===================*/
void Cloud::Update()
{
	//移動処理
	this->Move();
	//Warp処理
	this->Warp();
}

/*===================
描画処理
引数：なし
返り値：なし
===================*/
void Cloud::Draw()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->Draw();
	}
}

/*===================
移動処理:private
引数：なし
返り値：なし
===================*/
void Cloud::Move()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->SetPosition
		(
			DirectX::SimpleMath::Vector2
			(
				mpClouds[i]->GetPosition().x + CLOUD_VELOCITY,
				mpClouds[i]->GetPosition().y
			)
		);
	}
}

/*===================
ワープ処理:private
引数：なし
返り値：なし
===================*/
void Cloud::Warp()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		if (mpClouds[i]->GetPosition().x >= CLOUD_OVER_POSITION)
		{
			mpClouds[i]->SetPosition(DirectX::SimpleMath::Vector2(CLOUD_RESET_POSITION, mpClouds[i]->GetPosition().y));
		}		
	}
}
