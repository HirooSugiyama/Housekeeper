/*
�r���[�Ǝˉe�ƃJ�������W��ۑ����邽�߂̃C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#pragma once

class CameraInfoComponent
{
private:
	static std::unique_ptr <CameraInfoComponent> sCameraInfoComponent;

	static std::unique_ptr<DirectX::SimpleMath::Matrix> spView;
	static std::unique_ptr<DirectX::SimpleMath::Matrix> spProj;
	static std::unique_ptr<DirectX::SimpleMath::Vector3> spCameraPosition;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	CameraInfoComponent(const CameraInfoComponent& pv) = delete;
	CameraInfoComponent operator=(const CameraInfoComponent& pv) = delete;


	//�R���X�g���N�^
	CameraInfoComponent();
public:
	//���g�̃C���X�^���X
	static CameraInfoComponent& GetCameraInfoComponentInstance();

	//�ݒ�֐�
	void SetView(const DirectX::SimpleMath::Matrix& view);
	void SetProjection(const DirectX::SimpleMath::Matrix& proj);
	void SetCameraPosition(const DirectX::SimpleMath::Vector3& cameraPosition);

	//�擾�֐�
	DirectX::SimpleMath::Matrix* GetView() const;
	DirectX::SimpleMath::Matrix* GetProjection() const;
	DirectX::SimpleMath::Vector3* GetCameraPosition() const;
};