/*
�J�����̊��N���X
�쐬�ҁF���R
�쐬���F2021/10/24
*/
#include"pch.h"
#include "CameraBase.h"
// �J�����̋���
const float CameraBase::DEFAULT_CAMERA_DISTANCE = 5.0f;

// �J���������ԋ߂����e��
const float CameraBase::NEAR_PLANE = 1.f;
// �J���������ԉ������e��
const float CameraBase::FAR_PLANE = 1000.f;

/*==================================
�R���X�g���N�^
�����F�J�������W�A�^�[�Q�b�g�̍��W
�Ԃ�l�F�Ȃ�
==================================*/
CameraBase::CameraBase(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target)
	:
	mView(DirectX::SimpleMath::Matrix::Identity),
	mEye(eye),
	mTarget(target),
	mUp(0.0f, 1.0f, 0.0f)
{
}

/*=========================
�r���[�s��̎Z�o
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void CameraBase::CalculateViewMatrix()
{
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(mEye, mTarget, mUp);
}

/*=========================
�v���W�F�N�V�����s��̎Z�o
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void CameraBase::CalculateProjectionMatrix()
{
	const auto pDR = DX::DeviceResources::GetInstance();

	// �E�B���h�E�T�C�Y�̎擾
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	// ��p
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);
	// ��ʏc����
	float aspectRatio = width / height;

	//�ˉe�s������߂�
	mProjection = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

/*=========================
�s��v�Z
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================*/
void CameraBase::CalculationMatrix()
{
	this->CalculateViewMatrix();
	this->CalculateProjectionMatrix();
}
