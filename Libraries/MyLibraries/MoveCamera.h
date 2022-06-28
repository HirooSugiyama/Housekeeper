/*
�����J�����N���X
�쐬�ҁF���R
�쐬���F2021/12/05
*/
#pragma once

#include"CameraBase.h"


class MoveCamera :public CameraBase
{
private:
	//�΂˂̋���
	static const float SPRING_POWER;

public:
	//�R���X�g���N�^
	MoveCamera(const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& target);

	//�A�N�Z�T
	float GetSpringPower()const { return SPRING_POWER; }

};
