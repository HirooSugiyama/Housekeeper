/*
�ʏ�G�Փ˔���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#pragma once

//���N���X
#include"DetectEnemy.h"

class Enemy;			//����
class BulletManager;	//�����Ŏg�p
class Block;			//�����Ŏg�p
class Player;			//�����Ŏg�p
class Protecter;		//�����Ŏg�p
class DangerousLine;	//�����Ŏg�p

class DetectNormalEnemy :public DetectEnemy
{
private:

	//�G�̃v���C���[�ߑ��͈�
	static const float ENEMY_CAPTURE_RANGE;

	//�X�R�A�l
	static const int NORMAL_ENEMY_SCORE;


	//�G�|�C���^�ۑ��z��
	std::vector<Enemy*> mpChackColliderEnemy;

	//�T�C�Y�ȗ����ϐ�
	int mEnemySize;

	//�{�X�g�p�t���O
	bool mBossEnemyUseFlag;

public:


	//�R���X�g���N�^
	DetectNormalEnemy();
	//�f�X�g���N�^
	~DetectNormalEnemy();

	//�G�̉񐔕����������蔻����񂷏���
	int RoolBulletManagerChackhit(BulletManager* pBulletManager);

	//�u���b�N�ƓG�̓����蔻��
	void ChackHitBlocklEnemy(Block* pBlock);

	//�v���C���[�ƓG�̓����蔻��
	bool ChackHitPlayerEnemy(Player* pPlayer);
	int ChackHitNormalAttackPlayerEnemy(Player* pPlayer);	//�v���C���[�U�����̔���

	//���_�ƓG�̓����蔻��
	void ChackHitProtecterEnemy(Protecter* pProtecter);

	//�n��I�u�W�F�N�g�ƓG�̓����蔻��
	void ChackHitGroundObjectEnemy(AABB* pObjectCollider);

	//��ƓG�̓����蔻��
	void ChackHitWallNormalEnemy(AABB* pWallCollider);

	//�댯�M�����C���ƓG�̓����蔻��
	bool ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine);

	//�ΏۂƓG�̋�������
	void ChackDistanceTargetEnemy(const DirectX::SimpleMath::Vector3& position);

	//�A�N�Z�T
	void ResetChackColliderEnemy() { mpChackColliderEnemy.resize(0); }
	void SetChackColliderEnemy(std::vector<Enemy*> pEnemy)
	{
		mpChackColliderEnemy = pEnemy;
		mEnemySize = static_cast<int>(pEnemy.size());
	}
	void SetBossUseFlag(const bool& flag) { mBossEnemyUseFlag = flag; }
};
