/*
カメラの基底クラス
作成者：杉山
作成日：2021/10/24
*/
#pragma once



class CameraBase
{
private:

	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

	// カメラから一番近い投影面
	static const float NEAR_PLANE;
	// カメラから一番遠い投影面
	static const float FAR_PLANE;

	// ビュー行列
	DirectX::SimpleMath::Matrix mView;

	// プロジェクション行列
	DirectX::SimpleMath::Matrix mProjection;

	// カメラ座標
	DirectX::SimpleMath::Vector3 mEye;

	// 注視点
	DirectX::SimpleMath::Vector3 mTarget;

	// 上向きベクトル
	DirectX::SimpleMath::Vector3 mUp;

protected:
	//コンストラクタ
	CameraBase(DirectX::SimpleMath::Vector3 eye,DirectX::SimpleMath::Vector3 target);
	//デストラクタ
	virtual ~CameraBase() = default;


public:

	//更新処理
	virtual void Update(const DirectX::SimpleMath::Vector3& position){ UNREFERENCED_PARAMETER(position); }
	virtual void Update(){}

	//各種アクセサ
	// ビュー行列のアクセサ
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { mView = view; }
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return mView; }

	// プロジェクション行列のアクセサ
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { mProjection = projection; }
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return mProjection; }

	// カメラ座標のアクセサ
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye) { mEye = eye; }
	DirectX::SimpleMath::Vector3 GetEyePosition() const { return mEye; }

	// 注視点座標のアクセサ
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { mTarget = target; }
	DirectX::SimpleMath::Vector3 GetTargetPosition() const { return mTarget; }

	// 上向きベクトルのアクセサ
	void SetUpVector(const DirectX::SimpleMath::Vector3& up) { mUp = up; }
	DirectX::SimpleMath::Vector3 GetUpVector() const { return mUp; }



protected:
	//定数
	float GetCameraDistance() const { return DEFAULT_CAMERA_DISTANCE; }

	// ビュー行列の算出
	virtual void CalculateViewMatrix();

	// プロジェクション行列の算出
	virtual void CalculateProjectionMatrix();

public:
	//行列計算を行う
	void CalculationMatrix();	
};