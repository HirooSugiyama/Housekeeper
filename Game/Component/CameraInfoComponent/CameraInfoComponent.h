/*
ビューと射影とカメラ座標を保存するためのインターフェース
作成者：杉山
作成日：2021/10/21
*/

#pragma once

class CameraInfoComponent
{
private:
	static std::unique_ptr <CameraInfoComponent> sCameraInfoComponent;

	static std::unique_ptr<DirectX::SimpleMath::Matrix> spView;
	static std::unique_ptr<DirectX::SimpleMath::Matrix> spProj;
	static std::unique_ptr<DirectX::SimpleMath::Vector3> spCameraPosition;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	CameraInfoComponent(const CameraInfoComponent& pv) = delete;
	CameraInfoComponent operator=(const CameraInfoComponent& pv) = delete;


	//コンストラクタ
	CameraInfoComponent();
public:
	//自身のインスタンス
	static CameraInfoComponent& GetCameraInfoComponentInstance();

	//設定関数
	void SetView(const DirectX::SimpleMath::Matrix& view);
	void SetProjection(const DirectX::SimpleMath::Matrix& proj);
	void SetCameraPosition(const DirectX::SimpleMath::Vector3& cameraPosition);

	//取得関数
	DirectX::SimpleMath::Matrix* GetView() const;
	DirectX::SimpleMath::Matrix* GetProjection() const;
	DirectX::SimpleMath::Vector3* GetCameraPosition() const;
};