/*
�J�����̊��N���X
�쐬�ҁF���R
�쐬���F2021/10/24
*/
#pragma once



class CameraBase
{
private:

	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

	// �J���������ԋ߂����e��
	static const float NEAR_PLANE;
	// �J���������ԉ������e��
	static const float FAR_PLANE;

	// �r���[�s��
	DirectX::SimpleMath::Matrix mView;

	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix mProjection;

	// �J�������W
	DirectX::SimpleMath::Vector3 mEye;

	// �����_
	DirectX::SimpleMath::Vector3 mTarget;

	// ������x�N�g��
	DirectX::SimpleMath::Vector3 mUp;

protected:
	//�R���X�g���N�^
	CameraBase(DirectX::SimpleMath::Vector3 eye,DirectX::SimpleMath::Vector3 target);
	//�f�X�g���N�^
	virtual ~CameraBase() = default;


public:

	//�X�V����
	virtual void Update(const DirectX::SimpleMath::Vector3& position){ UNREFERENCED_PARAMETER(position); }
	virtual void Update(){}

	//�e��A�N�Z�T
	// �r���[�s��̃A�N�Z�T
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { mView = view; }
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return mView; }

	// �v���W�F�N�V�����s��̃A�N�Z�T
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { mProjection = projection; }
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return mProjection; }

	// �J�������W�̃A�N�Z�T
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye) { mEye = eye; }
	DirectX::SimpleMath::Vector3 GetEyePosition() const { return mEye; }

	// �����_���W�̃A�N�Z�T
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { mTarget = target; }
	DirectX::SimpleMath::Vector3 GetTargetPosition() const { return mTarget; }

	// ������x�N�g���̃A�N�Z�T
	void SetUpVector(const DirectX::SimpleMath::Vector3& up) { mUp = up; }
	DirectX::SimpleMath::Vector3 GetUpVector() const { return mUp; }



protected:
	//�萔
	float GetCameraDistance() const { return DEFAULT_CAMERA_DISTANCE; }

	// �r���[�s��̎Z�o
	virtual void CalculateViewMatrix();

	// �v���W�F�N�V�����s��̎Z�o
	virtual void CalculateProjectionMatrix();

public:
	//�s��v�Z���s��
	void CalculationMatrix();	
};