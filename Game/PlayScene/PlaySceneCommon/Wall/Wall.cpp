/*
�ǃN���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#include<pch.h>
#include"Wall.h"

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
Wall::Wall()
	:
	mpWallModel(nullptr)
{
	//���f���̃������m��
	mpWallModel = std::make_unique<BoxModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
Wall::~Wall()
{
}
/*===================================
����������
�����Fposition(���W)�Ascale(�g�嗦)
�Ԃ�l�F�Ȃ�
===================================*/
void Wall::Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 scale)
{

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__FULLFENCE));
	mpWallModel->SetModel(model);
	mpWallModel->SetPosition(position);
	mpWallModel->SetScale(scale);

		/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpWallModel->ReturnHalfSize(scale);
	//�ݒ�
	mpWallModel->SetAABBCollider(position - halfsize, position + halfsize);
}

/*===================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void Wall::Draw()
{
	mpWallModel->Draw();
}