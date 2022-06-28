/*
メインカメラ
作成者：杉山
作成日：2021/10/24
*/
#include "pch.h"
#include "Camera.h"


#include"CameraBase.h"


// 定数の初期化
//カメラ座標
const DirectX::SimpleMath::Vector3 Camera::EYE_TO_VEC(0.f, 23.f, 15.f);
//最初のターゲット座標
const DirectX::SimpleMath::Vector3 Camera::TARGET_INIT_TO_VEC(0.0f, 5.0f, 10.0f);	//カメラの動く前の座標
//ターゲット座標
const DirectX::SimpleMath::Vector3 Camera::TARGET_TO_VEC(0.0f, 1.0f, 6.0f);			//カメラが射す場所

//移動制限
const float Camera::MOVE_RESTRICTION_MAX_Z = 15.f;

/*=========================================
コンストラクタ
引数：なし
=========================================*/
Camera::Camera()
	:
	MoveCamera(EYE_TO_VEC, TARGET_INIT_TO_VEC),
	mRefEye(EYE_TO_VEC),
	mRefTarget(TARGET_INIT_TO_VEC),
	mUseEye(EYE_TO_VEC)
{
	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
}


/*=========================================
デストラクタ
=========================================*/
Camera::~Camera()
{
}


/*=========================================
更新処理
引数：注視点対象モデル座標
返り値：なし
=========================================*/
void Camera::Update(const DirectX::SimpleMath::Vector3& modelpos)
{
	auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();

	//注視点とカメラ位置を調節
	this->SetRefTargetPosition(modelpos - TARGET_TO_VEC);

	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition() +
		(mRefTarget - CameraBase::GetTargetPosition()) * MoveCamera::GetSpringPower()
	);


	this->SetRefEyePosition(modelpos + mUseEye - TARGET_TO_VEC);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition() +
		(mRefEye - CameraBase::GetEyePosition()) * MoveCamera::GetSpringPower()
	);
	
	//移動制限座標を越えていたら
	if (CameraBase::GetEyePosition().z > MOVE_RESTRICTION_MAX_Z) 
	{
		//変数を変換
		DirectX::SimpleMath::Vector3 limitPosition{ CameraBase::GetEyePosition() };
		limitPosition.z = MOVE_RESTRICTION_MAX_Z;

		//移動制限距離へ戻す
		CameraBase::SetEyePosition(limitPosition);
	}


	//ビュー変換
	CameraBase::CalculateViewMatrix();
	//シングルトンへ情報を保存
	pCiIF.SetView(CameraBase::GetViewMatrix());
	pCiIF.SetProjection(CameraBase::GetProjectionMatrix());
}

/*=========================================
更新処理
引数：なし
返り値：なし
=========================================*/
void Camera::Update()
{
	auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();

	//注視点とカメラ位置を調節
	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition()+
		(mRefTarget - CameraBase::GetTargetPosition()) * MoveCamera::GetSpringPower()
	);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition()+
		(mRefEye - CameraBase::GetEyePosition()) * MoveCamera::GetSpringPower()
	);

	//移動制限座標を越えていたら
	if (CameraBase::GetEyePosition().z > MOVE_RESTRICTION_MAX_Z)
	{
		//変数を変換
		DirectX::SimpleMath::Vector3 limitPosition{ CameraBase::GetEyePosition() };
		limitPosition.z = MOVE_RESTRICTION_MAX_Z;

		//移動制限距離へ戻す
		CameraBase::SetEyePosition(limitPosition);
	}


	//ビュー変換
	CameraBase::CalculateViewMatrix();
	//シングルトンへ情報を保存
	pCiIF.SetView(CameraBase::GetViewMatrix());
	pCiIF.SetProjection(CameraBase::GetProjectionMatrix());
}
