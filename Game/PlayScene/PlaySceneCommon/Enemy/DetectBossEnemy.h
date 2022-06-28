/*
�{�X�G�Փ˔���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#pragma once

//���N���X
#include"DetectEnemy.h"

//�O���錾
class BossEnemy;	//����
class Block;			//�����Ŏg�p
class Player;			//�����Ŏg�p
class BulletManager;	//�����Ŏg�p

class DetectBossEnemy : public DetectEnemy
{
private:

	//�{�X�G�̃X�R�A
	static const int BOSS_ENEMY_SCORE;

	//�z���G�|�C���^�ۑ��z��
	BossEnemy* mpChackColliderBossEnemy;

public:

	//�R���X�g���N�^
	DetectBossEnemy();
	//�f�X�g���N�^
	~DetectBossEnemy();


	//�G�̉񐔕����������蔻����񂷏���
	bool RoolBulletManagerChackhitBossEnemy(BulletManager* pBulletManager);


	//�u���b�N�ƃ{�X�G�̓����蔻��
	void ChackHitBlocklBossEnemy(Block* pBlock);

	//�v���C���[�ƃ{�X�G�̓����蔻��
	bool ChackHitPlayerBossEnemy(Player* pPlayer);
	bool ChackHitNormalAttackPlayerBossEnemy(Player* pPlayer);	//�v���C���[�U�����̔���

	//��ƓG�̓����蔻��
	void ChackHitWallBossEnemy(AABB* pWallCollider);

	//�{�X�͈͂ƃv���C���[�̏Փ˔���
	void ChackHitPlayerBossEnemyArea(Player* pPlayer);

	//�A�N�Z�T
	void ResetChackColliderEnemy() { mpChackColliderBossEnemy = nullptr; }
	void SetChackColliderEnemy(BossEnemy* pEnemy)
	{
		mpChackColliderBossEnemy = pEnemy;
	}

};
