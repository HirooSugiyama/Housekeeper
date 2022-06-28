/*
�r���[�Ǝˉe�ƃJ�������W��ۑ����邽�߂̃C���^�[�t�F�[�X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include<pch.h>

//�N���X�O���ŏ�����
std::unique_ptr <CameraInfoComponent> CameraInfoComponent::sCameraInfoComponent = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoComponent::spView = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoComponent::spProj = nullptr;
std::unique_ptr<DirectX::SimpleMath::Vector3> CameraInfoComponent::spCameraPosition = nullptr;

/*=========================================
�R���X�g���N�^
�����F�Ȃ�
=========================================*/
CameraInfoComponent::CameraInfoComponent()
{
	spView = std::make_unique<DirectX::SimpleMath::Matrix>();
	spProj = std::make_unique<DirectX::SimpleMath::Matrix>();
	spCameraPosition = std::make_unique<DirectX::SimpleMath::Vector3>();
}

/*=========================================
�C���X�^���X���擾
�����F�Ȃ�
�Ԃ�l�F���g�̃C���X�^���X
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
�r���[�s���ݒ肷��֐�
�����FMatrix�^	�r���[�s��
�Ԃ�l�F�Ȃ�
===========================*/
void CameraInfoComponent::SetView(const DirectX::SimpleMath::Matrix& view)
{
	*spView = view;
}

/*=========================================
�ˉe�s���ݒ肷��֐�
�����FMatrix�^�@�ˉe�s��
�Ԃ�l�F�Ȃ�
=========================================*/
void CameraInfoComponent::SetProjection(const DirectX::SimpleMath::Matrix& proj)
{
	*spProj = proj;
}

/*=========================================
���݂̃J�����̍��W��ݒ肷��֐�
�����FVector�^�@�J�����̍��W
�Ԃ�l�F�Ȃ�
=========================================*/
void CameraInfoComponent::SetCameraPosition(const DirectX::SimpleMath::Vector3& cameraPosition)
{
	*spCameraPosition = cameraPosition;
}

/*=================
�擾�֐�
�����F�Ȃ�
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
