/*
�h�q�t�F�[�Y
�쐬�ҁF���R
�쐬���F2021/06/16
*/
#pragma once

//���N���X
#include"PlayScenePhaseBase.h"

//����
#include"../PlaySceneDefence/DangerousLine.h"
#include"../PlaySceneDefence/PreparingBlock.h"

#include"../PlaySceneCommon/Enemy/DetectNormalEnemy.h"
#include"../PlaySceneCommon/Enemy/DetectSubordinateEnemy.h"
#include"../PlaySceneCommon/Enemy/DetectBossEnemy.h"

class PScenePhaseDefense :public PlayScenePhaseBase
{
private:
	//���݂̏��
	enum class eDefenseState
	{
		MOVE,	//�ړ����
		PIXED,	//��_�J�������_���
	};


	//��_�J�����̍��W
	static const DirectX::SimpleMath::Vector3 PIXED_CAMERA_POSITION;


	//PlayScene�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;

	//�I�u�W�F�N�g
	std::unique_ptr<DangerousLine> mpDangerousLine;
	std::unique_ptr <PreparingBlock> mpSampleBlock;

	//�Փ˔��菈��
	std::unique_ptr<DetectNormalEnemy> mpDetectNormalEnemy;
	std::unique_ptr<DetectSubordinateEnemy> mpDetectSubordinateEnemy;
	std::unique_ptr<DetectBossEnemy> mpDetectBossEnemy;

	//�ԐF�_�Ńt���O
	bool mRedAssertFlag;

	//�t�F�[�Y�J�E���g
	int mPhaseCount;

	//�݌v�t�F�[�Y��
	int mAllPhaseNum;

	//�V���b�v�N���t���O
	bool mShopOpenFlag;

	//�񋓌^�̎��̉�
	eDefenseState mDefenseState;

	//�ړ��J�������W�ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3 mMoveCameraSavePosition;

	//���C�v�t���O
	bool mWipeFlag;

public:
	//�R���X�g���N�^
	PScenePhaseDefense();
	//�f�X�g���N�^
	~PScenePhaseDefense();
	
	//������
	void Initialize(PlayScene* pPlayScene)override;

	//�X�V
	void Update()override;

	//State�ύX�O�̃��Z�b�g����
	void Reset()override;

	//�`��
	void Draw()override;

private:

	//�I�u�W�F�N�g�̍X�V����
	void ObjectUpdate();
	//�����蔻��̏���
	void ColliderUpdate();
	//�I�u�W�F�N�g�̕`�揈��
	void ObjectDraw();

	//�ԐF�_�ŃG�t�F�N�g�����邩�ǂ���
	void RedAssertSet();

	//�t�F�[�Y�X�V����
	void PhaseToUpdate();

	//�J�������_�؂�ւ�����
	void ChangeCamera();
};