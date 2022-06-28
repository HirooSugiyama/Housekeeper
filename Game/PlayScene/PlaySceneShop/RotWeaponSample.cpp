/*
武器モデルを回転させるだけのクラス
作成者：杉山
作成日：2021/10/15
*/
#include"pch.h"

#include"RotWeaponSample.h"

//座標
const DirectX::SimpleMath::Vector3 RotWeaponSample::ROTMODEL_POSITION(3.5f,1.f,0.f);
//拡大率
const DirectX::SimpleMath::Vector3 RotWeaponSample::ROTMODEL_SCALE(1.5f, 1.5f, 1.5f);
//回転速度
const float RotWeaponSample::ROT_SPEED = 0.5f;

/*===================================
コンストラクタ
引数：なし
===================================*/
RotWeaponSample::RotWeaponSample()
	:
	mpRotModel(nullptr),
	mModelRot(0.f)
{
	mpRotModel = std::make_unique<ObjectModel>();
}

/*===================================
デストラクタ
===================================*/
RotWeaponSample::~RotWeaponSample()
{
}

/*=================================
初期化処理
引数：なし
返り値：なし
===================================*/
void RotWeaponSample::Initialize()
{
	//拡大率と座標をあらかじめ設定しておく
	mpRotModel->SetPosition(ROTMODEL_POSITION);
	mpRotModel->SetScale(ROTMODEL_SCALE);
}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
void RotWeaponSample::Update()
{
	//モデルを回転させる
	float rot = mpRotModel->GetRotAngleY() + ROT_SPEED;
	mpRotModel->SetRotationY(rot);
}

/*=================================
描画処理
引数：なし
返り値：なし
===================================*/
void RotWeaponSample::Draw()
{
	//もしモデル情報が入っていたら
	if (mpRotModel->GetModel() != nullptr)
	{
		//モデルを描画する
		mpRotModel->Draw();
	}
}

/*==================================
リセット処理
引数：なし
返り値：なし
===================================*/
void RotWeaponSample::Reset()
{
	mModelRot = 0.f;
}

/*===================================
モデル情報を取得する
引数：モデル情報
返り値：なし
===================================*/
void RotWeaponSample::SetWeaponModel(DirectX::Model* model)
{
	mpRotModel->SetModel(model);
}




