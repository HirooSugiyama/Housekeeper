/*
ビューと射影とカメラ座標を保存するためのインターフェース
作成者：杉山
作成日：2021/10/21
*/

#include<pch.h>

//クラス外部で初期化
std::unique_ptr <CameraInfoComponent> CameraInfoComponent::sCameraInfoComponent = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoComponent::spView = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoComponent::spProj = nullptr;
std::unique_ptr<DirectX::SimpleMath::Vector3> CameraInfoComponent::spCameraPosition = nullptr;

/*=========================================
コンストラクタ
引数：なし
=========================================*/
CameraInfoComponent::CameraInfoComponent()
{
	spView = std::make_unique<DirectX::SimpleMath::Matrix>();
	spProj = std::make_unique<DirectX::SimpleMath::Matrix>();
	spCameraPosition = std::make_unique<DirectX::SimpleMath::Vector3>();
}

/*=========================================
インスタンスを取得
引数：なし
返り値：自身のインスタンス
=========================================*/
CameraInfoComponent& CameraInfoComponent::GetCameraInfoComponentInstance()
{
	if (sCameraInfoComponent == nullptr)
	{
		sCameraInfoComponent.reset(new CameraInfoComponent());
	}
	return *sCameraInfoComponent.get();
}


/*==========================
ビュー行列を設定する関数
引数：Matrix型	ビュー行列
返り値：なし
===========================*/
void CameraInfoComponent::SetView(const DirectX::SimpleMath::Matrix& view)
{
	*spView = view;
}

/*=========================================
射影行列を設定する関数
引数：Matrix型　射影行列
返り値：なし
=========================================*/
void CameraInfoComponent::SetProjection(const DirectX::SimpleMath::Matrix& proj)
{
	*spProj = proj;
}

/*=========================================
現在のカメラの座標を設定する関数
引数：Vector型　カメラの座標
返り値：なし
=========================================*/
void CameraInfoComponent::SetCameraPosition(const DirectX::SimpleMath::Vector3& cameraPosition)
{
	*spCameraPosition = cameraPosition;
}

/*=================
取得関数
引数：なし
=================*/
DirectX::SimpleMath::Matrix* CameraInfoComponent::GetView() const
{
	return spView.get();
}

DirectX::SimpleMath::Matrix* CameraInfoComponent::GetProjection() const
{
	return spProj.get();
}

DirectX::SimpleMath::Vector3* CameraInfoComponent::GetCameraPosition() const
{
	return spCameraPosition.get();
}
