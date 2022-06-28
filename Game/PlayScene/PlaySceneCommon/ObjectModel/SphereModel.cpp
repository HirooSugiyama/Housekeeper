/*
���̓����蔻������������f���N���X
�쐬�ҁF���R
�쐬���F2021/06/12
*/

#include"pch.h"
#include"SphereModel.h"

//�����蔻�菉���l
const float SphereModel::InitCollider = 0.f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
SphereModel::SphereModel()
	:
	ObjectModel(),
	mpSphereCollider()
{
	mpSphereCollider = std::make_unique<Sphere>();
	mpSphereCollider->mRadius = InitCollider;
}

/*===================================
�f�X�g���N�^
===================================*/
SphereModel::~SphereModel()
{
}

/*===================================
�����蔻��̐ݒ�
�����F�������W�A���a
�Ԃ�l�F�Ȃ�
===================================*/
void SphereModel::SetSphereCollider(const DirectX::SimpleMath::Vector3& center, float radius)
{
	mpSphereCollider->mCenter = center;
	mpSphereCollider->mRadius = radius;
}