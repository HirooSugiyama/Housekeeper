/*
�z���G�Փ˔���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#pragma once

//���N���X
#include"DetectEnemy.h"

//�O���錾
class SubordinateEnemy;	//����
class Block;			//�����Ŏg�p
class Player;			//�����Ŏg�p
class BulletManager;			//�����Ŏg�p

class DetectSubordinateEnemy: public DetectEnemy
{
private:

	//�z���G�̃X�R�A
	static const int SUBORDINATE_ENEMY_SCORE;

	//�z���G�|�C���^�ۑ��z��
	std::vector<SubordinateEnemy*> mpChackColliderSubordinateEnemy;
	//�ȗ����p�ϐ�
	int mEnemySize;


public:

	//�R���X�g���N�^
	DetectSubordinateEnemy();
	//�f�X�g���N�^
	~DetectSubordinateEnemy();

	//�G�̉񐔕����������蔻����񂷏���
	void RoolBulletManagerChackhitSubordinateEnemy(BulletManager* pBulletManager);

	//�u���b�N�Ɣz���G�̓����蔻��
	void ChackHitBlocklSubordinateEnemy(Block* pBlock);

	//�v���C���[�Ɣz���G�̓����蔻��
	bool ChackHitPlayerSubordinateEnemy(Player* pPlayer);
	void ChackHitNormalAttackPlayerSubordinateEnemy(Player* pPlayer);	//�v���C���[�U�����̔���

	//�A�N�Z�T
	void ResetChackColliderEnemy() { mpChackColliderSubordinateEnemy.resize(0); }
	void SetChackColliderEnemy(std::vector<SubordinateEnemy*> pEnemy)
	{
		mpChackColliderSubordinateEnemy = pEnemy;
		mEnemySize = static_cast<int>(pEnemy.size());
	}
private:
	//�g�p���Ă���z���G�S�Ă��~������
	void AllSubordinateEnemyStop();
};
