/*
定点カメラ
作成者：杉山
作成日：2021/10/24
*/
#include "pch.h"
#include "FixedPointCamera.h"

#include "DeviceResources.h"

//カメラ座標
const DirectX::SimpleMath::Vector3 FixedPointCamera::EYE_TO_VEC(0.0f, 2.0f, 10.0f);
/*===============================
コンストラクタ
引数：なし
===============================*/
FixedPointCamera::FixedPointCamera()
	:
	CameraBase(EYE_TO_VEC, DirectX::SimpleMath::Vector3::Zero)
{
	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
}


/*===============================
デストラクタ
===============================*/
FixedPointCamera::~FixedPointCamera()
{
}
