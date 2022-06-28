/*
�A�j���[�V�������f��
�쐬�ҁF���R
�쐬���F2021/12/26
*/
#pragma once

#include"../ObjectModel.h"

class AnimationModel 
{
private:

	//���f��
	std::unique_ptr<ObjectModel> mpModel;

	//�{�[��
	DirectX::ModelBone::TransformArray mBones;

	//�A�j���[�V����
	DX::AnimationCMO* mpAnimation;

	//�F�g�p�t���O
	bool mColorFlag;
	//�F
	DirectX::SimpleMath::Vector3 mColor;



public:

	//�R���X�g���N�^
	AnimationModel();
	//�f�X�g���N�^
	~AnimationModel();
	//����������
	void Initialize(const int& fileKey);
	//�X�V����
	void Update(const float& deltaTime);

	//�`�揈��
	void Draw();

	ObjectModel* GetModel() const { return mpModel.get(); }

	//�F�g�p�t���O
	bool GetColorFlag() { return mColorFlag; }
	//�F�̐ݒ�
	void SetColor(const DirectX::SimpleMath::Vector3& color)
	{
		//�F��ݒ肷��
		mColor = color;
		mColorFlag = true;
	}
	//�t���O������
	void DownColorFlag() { mColorFlag = false; }
	//�F���擾
	DirectX::SimpleMath::Vector3 GetColor() const { return mColor; }

private:

	//�F�ݒ�
	void UpdateColor();

};
