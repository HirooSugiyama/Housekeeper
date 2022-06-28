/*
動くカメラクラス
作成者：杉山
作成日：2021/12/05
*/

#include"pch.h"
#include"MoveCamera.h"


//ばねの強さ
const float MoveCamera::SPRING_POWER = 0.05f;

/*===============================
コンストラクタ
引数：カメラ座標、カメラ注視点
===============================*/

MoveCamera::MoveCamera
(
	const DirectX::SimpleMath::Vector3& eye,
	const DirectX::SimpleMath::Vector3& target
)
	:
	CameraBase(eye,target)
{
}
