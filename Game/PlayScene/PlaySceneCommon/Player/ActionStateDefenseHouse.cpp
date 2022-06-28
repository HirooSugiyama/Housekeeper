/*
�v���C���[�̍s����ԕ����X�e�[�g�p�^�[��
�쐬�ҁF���R
�쐬���F2021/09/14
*/

#include"pch.h"
#include "ActionStateDefenseHouse.h"


/*=====================================
�R���X�g���N�^
�����F�Ȃ�
=====================================*/
ActionStateDefenseHouse::ActionStateDefenseHouse()
	:
	ActionStateBase(),
	mpBlockCreate(nullptr),
	mDefenseHouseState(eDefenseActionState::BLOCK_CREATE)
{
	mpBlockCreate = std::make_unique<DefenseActionBlockCreate>();
}

/*=====================================
�f�X�g���N�^
=====================================*/
ActionStateDefenseHouse::~ActionStateDefenseHouse()
{
}

/*=====================================
����������
�����F�v���C���[�̃|�C���^
�Ԃ�l�F�Ȃ�
=====================================*/
void ActionStateDefenseHouse::Initialize(Player* pPlayer)
{
	//�ǌ������̏���������
	mpBlockCreate->Initialize(pPlayer);
}


/*====================================
�ǌ��N���X�Ŏg�p����|�C���^�ۑ�����
�����F���{�p�u���b�N�N���X�̃|�C���^
		�u���b�N�Ǘ��N���X�̃|�C���^
�Ԃ�l�F�Ȃ�
=====================================*/
void ActionStateDefenseHouse::SetCreateBlockPointer(
		PreparingBlock* pPreparingBlock,
		BlockManager* pBlockManager)
{
	//�|�C���^��ۑ�����
	mpBlockCreate->SetPointer(pPreparingBlock, pBlockManager);
}


/*=====================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================================*/
void ActionStateDefenseHouse::Update()
{
	//�ǌ��N���X�̍X�V����
	mpBlockCreate->Create();
}

/*=====================================
State�J�n���̏���������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================================*/
void ActionStateDefenseHouse::Reset()
{

}

/*=====================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================================*/
void ActionStateDefenseHouse::Draw()
{
	//�ǌ������̕`�揈��
	mpBlockCreate->Draw();
}