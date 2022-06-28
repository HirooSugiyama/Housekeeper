/*
�G���N���X
�쐬�ҁF���R
�쐬���F2022/02/11
*/
#include"pch.h"

#include"IEnemy.h"



//���\�[�X�̎擾
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"



//���f���̊g�嗦
//�����ڗp
const DirectX::SimpleMath::Vector3 IEnemy::ENEMY_SCALE(0.5f, 0.5f, 0.5f);

//���f���ɍ��킹�ē����蔻��p�̊g�嗦���߂�
//�v���C���[��Z������Y�����ɒ����̂œ����蔻���Z������Y�����ɐL�΂�
const float IEnemy::ENEMY_COLLIDER_EXTEND_Y = 3.f;
const float IEnemy::ENEMY_COLLIDER_EXTEND_Z = 4.f;


//���f���������~�X�̏C��
const float IEnemy::ENMEY_MODELMISS_FIX_ROT = 180.f;

//�G�t�F�N�g�\�����W
const DirectX::SimpleMath::Vector3 IEnemy::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);



//�_���[�W�l�̕`����W
const DirectX::SimpleMath::Vector3 IEnemy::FLOATNUMBER_DISTANCE_POSITION(0.f, 4.5f, 0.f);


/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
IEnemy::IEnemy()
	:mpEnemyModel(),
	mpEnemyShadow(nullptr),
	mpFloatNumber(nullptr),
	mEnemyDamage(0)
{
	mpEnemyModel = std::make_unique<BoxModel>();

	mpEnemyShadow = std::make_unique<Shadow>();
	mpFloatNumber = std::make_unique<FloatNumber3D>();
}

/*===================================
�f�X�g���N�^
===================================*/
IEnemy::~IEnemy()
{
}

/*===================================
�I������(����)
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void IEnemy::Finalize()
{
	mpEnemyModel.reset();
}


/*=================================
�_���[�W��^���鏈��
�����F�_���[�W�l�AHP�ő�l
�Ԃ�l�F���j�������ǂ���(true�F���j)
===================================*/
bool IEnemy::Damage(const int& damagenum, const int& maxHitPoint)
{
	//�_���[�W��^����
	mEnemyDamage += damagenum;

	if (mEnemyDamage >= maxHitPoint)
	{
		//���g�p��Ԃɂ���
		this->SelfDestroy();
		//�G�t�F�N�g�}�l�[�W���[�̎擾
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::DISAPPEAR);
		effect->SetPosition(IEnemy::GetEnemyModel()->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		return true;
	}
	return false;
}

/*==================================
���g���폜(�|�C���^�Ȃǂ͏��ł��Ȃ�)
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void IEnemy::SelfDestroy()
{
	//�`�撆�ł����
	if (mpEnemyModel->GetDrawFlag())
	{
		//�����蔻��������l��
		mpEnemyModel->SetAABBCollider
		(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Vector3::Zero
		);

		//���g�p��Ԃɂ���
		mpEnemyModel->SetModelUseFlag(false);

		//�_���[�W�������l�ɖ߂�
		mEnemyDamage = 0;
	}
}

/*=================================
�G�t�F�N�g���쐬����
�����G�_���[�W�l
�Ԃ�l�F�Ȃ�
===================================*/
void IEnemy::CreateNumberEffect(int damageNum)
{
	mpFloatNumber->Create
	(
		damageNum,
		IEnemy::GetEnemyModel()->GetPosition() +
		FLOATNUMBER_DISTANCE_POSITION
	);
}

/*=================================
�G�t�F�N�g�����Z�b�g����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void IEnemy::ResetNumberEffect()
{
	mpFloatNumber->Reset();
}

