/*
�j�t���̃��f�����Ǘ�����N���X
�쐬�ҁF���R
�쐬���F2021/08/19
*/

#include"pch.h"

#include "GroundObjectShop.h"


//�V���b�v���f���̊g�嗦
const DirectX::SimpleMath::Vector3 GroundObjectShop::SHOP_SCALE(4.f, 4.f, 4.f);
//�V���b�v���f����Y���W
const float GroundObjectShop::SHOP_MODEL_POSITION_Y = 1.f;


/*======================
�R���X�g���N�^
�����F�Ȃ�
======================*/
GroundObjectShop::GroundObjectShop()
	:
	IGroundObject(),
	mpShopModel(nullptr)
{
	mpShopModel = std::make_unique<ObjectModel>();
}

/*======================
�f�X�g���N�^
======================*/
GroundObjectShop::~GroundObjectShop()
{

}

/*======================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
======================*/
void GroundObjectShop::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__SHOP));

	//���f���̐ݒ�
	mpShopModel->SetModel(model);
	//�g�嗦�̐ݒ�
	mpShopModel->SetScale(SHOP_SCALE);
}

/*======================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
======================*/
void GroundObjectShop::Draw()
{
	mpShopModel->Draw();
}

/*====================================
���f���̍��W��ݒ肷��
�����F���f���̍��W
�Ԃ�l�F�Ȃ�
====================================*/
void GroundObjectShop::SetShopModelPosition(const DirectX::SimpleMath::Vector3& position)
{
	mpShopModel->SetPosition(position);
}
