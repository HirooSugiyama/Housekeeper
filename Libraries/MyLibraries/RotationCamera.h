/*
旋回カメラ
作成者：杉山
作成日：2021/10/11
*/
#pragma once



//基底クラス
#include"MoveCamera.h"

class RotationCamera :public MoveCamera
{
private:

	//カメラの移動スピード
	static const float CAMERA_MOVE_SPEED;

	//カメラ初期座標
	static const DirectX::SimpleMath::Vector3 CAMERA_INIT_EYE_POSITION;
	//ターゲット座標
	static const DirectX::SimpleMath::Vector3 CAMERA_INIT_TARGET;
	//カメラの回転速度
	static const float CAMERA_ROT_SPEED;

	//注視点とカメラ座標の距離
	static const DirectX::SimpleMath::Vector3 ROT_CAMERA_DISTANCE;

	//ばねの強度
	static const float SPRING_POWER;


	// 参照視点
	DirectX::SimpleMath::Vector3 mRefEye;

	// 参照注視点
	DirectX::SimpleMath::Vector3 mRefTarget;

	//回転値
	float mRot;

public:
	// コンストラクタ
	RotationCamera();

	// デストラクタ
	~RotationCamera();

	//更新処理
	void Update();

	// カメラ座標のアクセサ
	void SetRefEyePosition(const DirectX::SimpleMath::Vector3& eye) { mRefEye = eye; }
	DirectX::SimpleMath::Vector3 GetRefEyePosition() const { return mRefEye; }

	// 参照注視点座標のアクセサ
	void SetRefTargetPosition(const DirectX::SimpleMath::Vector3& target) { mRefTarget = target; }
	DirectX::SimpleMath::Vector3 GetRefTargetPosition() const { return mRefTarget; }

	//移動処理
	void Move();

	//カメラ座標リセット処理
	void Reset(const DirectX::SimpleMath::Vector3& position);
};
