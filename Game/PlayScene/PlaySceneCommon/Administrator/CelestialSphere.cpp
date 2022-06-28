/*
天球クラス
作成者：杉山
作成日：2021/06/19
*/
#include"pch.h"
#include "CelestialSphere.h"

//天球の半径
const DirectX::SimpleMath::Vector3 CelestialSphere::SPHERE_RADIUS(3.f, 3.f, 3.f);

//カラーを最大値に
const DirectX::SimpleMath::Vector3 CelestialSphere::MAX_COLOR_NUM(1.f, 1.f,1.f);

/*=========================
コンストラクタ
引数：なし
=========================*/
CelestialSphere::CelestialSphere()
	:
	mpSphere(nullptr)
{
	mpSphere = std::make_unique<ObjectModel>();
}

/*=========================
デストラクタ
=========================*/
CelestialSphere::~CelestialSphere()
{
}

/*=======================
初期化処理
引数：なし
返り値：なし
=========================*/
void CelestialSphere::Initialize()
{

	//使用する変数の宣言
	DirectX::SimpleMath::Vector3 scale = SPHERE_RADIUS;

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();	//リソースマネージャーのインスタンス取得
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__SKYDOME_DAYTIME));	//キー指定


	//天球モデルの設定
	mpSphere->SetModel(model);								//モデルのセット
	mpSphere->SetPosition(DirectX::SimpleMath::Vector3::Zero);	//座標は原点
	mpSphere->SetScale(scale);								//拡大率は等倍(元が大きい)

	//エフェクトの設定
	mpSphere->GetModel()->UpdateEffects([&](DirectX::IEffect* effect)
		{
			DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights) 
			{
				// ライトの影響をなくす
				lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3::Zero);
				lights->SetLightEnabled(static_cast<int>(eWhichLight::_0), false);
				lights->SetLightEnabled(static_cast<int>(eWhichLight::_1), false);
				lights->SetLightEnabled(static_cast<int>(eWhichLight::_2), false);
			}

			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect) 
			{
				// エミッション色を白に設定する
				basicEffect->SetEmissiveColor(MAX_COLOR_NUM);
			}
		});
}

/*=========================
描画処理
引数：なし
返り値：なし
=========================*/
void CelestialSphere::Draw()
{
	mpSphere->Draw();
}

/*=========================
天球を変える
引数：なし
返り値：なし
=========================*/
void CelestialSphere::ChangeSphereModelNight()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__SKYDOME_NIGHTTIME));
	mpSphere->SetModel(model);			//モデルのセット
}

void CelestialSphere::ChangeSphereModelDay()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__SKYDOME_DAYTIME));
	mpSphere->SetModel(model);			//モデルのセット
}
