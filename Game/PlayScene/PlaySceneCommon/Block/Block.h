/*
��Q���N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/

#pragma once




//����
#include"../../PlaySceneCommon/ObjectModel/BoxModel.h"
//State����
#include"BKStateNormal.h"
#include"BKStateArchitecture.h"

class BlockKindBase;		//��ԕ������N���X

class Block
{
private:

	//�萔
	//�u���b�N�̑ϋv�x
	static const int BLOCK_DURABILITY;


	//�ϐ�

	//���f���`��N���X
	std::unique_ptr<BoxModel> mpBlockModel;

	//�g�p�t���O
	bool mBlockUseFlag;

	//HP
	int mBlockHP;

	//�d�̓t���O
	bool mIsGravity;

	//�^�Ԃɂ���Đ؂�ւ���
	std::unique_ptr<BKStateArchitecture> mpArchitecture;
	std::unique_ptr<BKStateNormal> mpNormal;

	//�^��
	BlockKindBase* mpBlockKindBase;

public:
	//�֐�
	//�R���X�g���N�^
	Block();
	//�f�X�g���N�^
	~Block();
	//������
	void Initialize();
	//�X�V
	void Update();

	//��������
	void Create(const DirectX::SimpleMath::Vector3& position,
				const DirectX::SimpleMath::Vector3& scale);

	//�`��
	void Draw();
	//�I������
	void Finalize();

	//���f���ɃA�N�Z�X(�����蔻��Ȃ�)
	BoxModel* GetBoxModel() const
	{
		return mpBlockModel.get();
	}

	//���g���폜(�|�C���^�Ȃǂ͏��ł��Ȃ�)
	void SelfDestroy();


	//�g�p�t���O��Ԃ��֐�
	bool GetBlockUseFlag() const { return mBlockUseFlag; }
	bool* GetBlockUseFlagAddress()  { return &mBlockUseFlag; }

		//�ǂɃ_���[�W��^����
	bool BlockDamage(const int& damagenum)
	{
		mBlockHP -= damagenum; 
		if (mBlockHP <= 0) 
		{
			return true;
		}
		return false;
	}

	//�ǂ̑ϋv�l�̃A�N�Z�T
	int GetBlockHP()const { return mBlockHP; }

	//�u���b�N�̌^�Ԃ�ς���
	void ChangeStateNormal() { mpBlockKindBase = (BlockKindBase*)mpNormal.get(); }
	void ChangeStateArchitecture() { mpBlockKindBase = (BlockKindBase*)mpArchitecture.get(); }
};