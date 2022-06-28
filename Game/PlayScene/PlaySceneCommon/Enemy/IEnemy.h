/*
�G���N���X
�쐬�ҁF���R
�쐬���F2022/02/11
*/
#pragma once

//����
#include "Game/PlayScene/PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../Shadow.h"
#include"../../PlaySceneDefence/FloatNumber3D.h"

class CameraBase;

class IEnemy
{
private:

	//�g�嗦
	static const DirectX::SimpleMath::Vector3 ENEMY_SCALE;
	//���f���ɍ��킹�ē����蔻��p�̊g�嗦���߂�
	static const float ENEMY_COLLIDER_EXTEND_Y;
	static const float ENEMY_COLLIDER_EXTEND_Z;
	//���f���������~�X�̏C��
	static const float ENMEY_MODELMISS_FIX_ROT;


	//�G�t�F�N�g�\�����W
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;


	//�_���[�W�l�̕`����W
	static const DirectX::SimpleMath::Vector3 FLOATNUMBER_DISTANCE_POSITION;

	//���f���`��N���X
	std::unique_ptr<BoxModel> mpEnemyModel;

	//�e
	std::unique_ptr<Shadow> mpEnemyShadow;

	//�����G�t�F�N�g
	std::unique_ptr<FloatNumber3D> mpFloatNumber;

	//���݂�HP
	int mEnemyDamage;

public:

	//�R���X�g���N�^
	IEnemy();
	//�f�X�g���N�^
	virtual ~IEnemy();
	//����������
	virtual void Initialize(const DirectX::SimpleMath::Vector3& position) = 0;
	//�X�V����
	virtual void Update() = 0;
	//�`�揈��
	virtual void Draw() = 0;
	//�I������
	void Finalize();

	//�_���[�W��^���鏈��
	bool Damage(const int& damagenum, const int& maxHitPoint);

	//���g���폜����B
	void SelfDestroy();

	//�G�t�F�N�g���쐬����
	void CreateNumberEffect(int damageNum);
	//�G�t�F�N�g�����Z�b�g����
	void ResetNumberEffect();


	//���ʂ̏�ԕύX����
	virtual void ChangeStateCreateBefore() = 0;
	virtual void ChangeStateDisappearance() = 0;
	virtual void ChangeStateMove() = 0;

	//�A�N�Z�T
	//�J�����|�C���^�̕ۑ�
	void SaveCameraPointer(CameraBase* camera) { mpFloatNumber->Initialize(camera); }

	BoxModel* GetEnemyModel()const { return mpEnemyModel.get(); }
	//�e�̃A�N�Z�T
	Shadow* GetShadow()const { return mpEnemyShadow.get(); }
	FloatNumber3D* GetFloatNumber3D()const { return mpFloatNumber.get(); }

	//�萔�̃A�N�Z�T
	DirectX::SimpleMath::Vector3 GetEnemyScale()const { return ENEMY_SCALE; }
	float GetEnemyColliderExtendY() const { return ENEMY_COLLIDER_EXTEND_Y; }
	float GetEnemyColliderExtendZ() const { return ENEMY_COLLIDER_EXTEND_Z; }
	float GetEnemyModelMissFixRotation() const { return ENMEY_MODELMISS_FIX_ROT; }

	//���݂�HP�̃A�N�Z�T
	int GetEnemyDamage()const { return mEnemyDamage; }

	//�G��HP�̃A�N�Z�T
	virtual int GetEnemyHP() = 0;
};
