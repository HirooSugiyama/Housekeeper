/*
アニメーションモデル
作成者：杉山
作成日：2021/12/26
*/
#include"pch.h"

#include"AnimationModel.h"
#include"Game/Manager/ResourceManager.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
AnimationModel::AnimationModel()
	:mpModel()
	,mBones()
	,mpAnimation()
{
	mpModel = std::make_unique<ObjectModel>();
}

/*=================================
デストラクタ
===================================*/
AnimationModel::~AnimationModel()
{
	mpModel.reset();
}

/*=================================
初期化処理
引数：ファイルのキー情報
返り値：なし
===================================*/
void AnimationModel::Initialize(const int& fileKey)
{
	//リソースマネージャから情報を取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	AnimModel* animModel = pRM->GetAnimationCmoModel(fileKey);

	//情報の保存
	mpModel->SetModel(animModel->mModel.get());

	mpAnimation = &animModel->mAnim;

	mpAnimation->Bind(*mpModel->GetModel());

	mBones = DirectX::ModelBone::MakeArray(mpModel->GetModel()->bones.size());

	mpModel->GetModel()->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto skin = dynamic_cast<DirectX::SkinnedEffect*>(effect);
			if (skin)
			{
				skin->SetPerPixelLighting(true);
			}
		});


}
/*===================================
更新処理
引数：時間
返り値：なし
===================================*/
void AnimationModel::Update(const float& deltaTime)
{
	//アニメーション更新処理
	mpAnimation->Update(deltaTime);

	//モデル更新処理(色変え)
	mpModel->Update();
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void AnimationModel::Draw()
{
	const auto pDeviceResources = DX::DeviceResources::GetInstance();
	const auto& pCameraInfoComponent = CameraInfoComponent::GetCameraInfoComponentInstance();
	const auto& pDirectXtkComponent = DirectXtkComponent::GetDirectXtkComponentInstance();

	// デバイスコンテキストの取得
	auto context = pDeviceResources->GetD3DDeviceContext();

	//色が設定してある場合のみ処理を通す
	//色変え処理
	this->UpdateColor();

	//ボーンのサイズを取得
	size_t nbones = mpModel->GetModel()->bones.size();

	mpAnimation->Apply(*mpModel->GetModel(), nbones, mBones.get());

	//ワールド座標を計算しておく
	mpModel->CalculationWorldMatrix();

	mpModel->GetModel()->DrawSkinned
	(
		context,
		*pDirectXtkComponent.GetCommonStates(),
		nbones,
		mBones.get(),
		mpModel->GetWorld(),
		*pCameraInfoComponent.GetView(),
		*pCameraInfoComponent.GetProjection()
	);
}

/*==================================
色更新処理
引数：なし
返り値：なし
===================================*/
void AnimationModel::UpdateColor()
{
	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 color{ DirectX::Colors::Gray };

	//フラグが立っているときのみ指定する
	if (mColorFlag)
	{
		color = mColor;
	}
	else
	{
		return;
	}

	//色設定
	mpModel->GetModel()->UpdateEffects
	(
		[=](DirectX::IEffect* effect)
		{
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightingEnabled(true);
				lights->SetPerPixelLighting(true);
				lights->SetLightEnabled(0, true);
				lights->SetLightDiffuseColor(0, color);
				lights->SetLightEnabled(1, true);
				lights->SetLightDiffuseColor(1, color);
				lights->SetLightEnabled(2, true);
				lights->SetLightDiffuseColor(2, color);
			}
		}
	);
}
