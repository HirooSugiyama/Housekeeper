/*
��Q���Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once

//����
#include"Block.h"

//�O���錾
//�����蔻��p
class PreparingBlock;
class Player;
class Administrator;
class Bullet;
class Camera;
class DetectNormalEnemy;
class DetectSubordinateEnemy;
class DetectBossEnemy;

//�|�C���^�ۑ��p
class EnemyManager;


class BlockManager
{
private:
	//�萔
	//�ǂ̏�����
	static const int BLOCK_MAXNUM = 500;

	//�����_���[�W
	static const int EXPLOSION_BLOCK_DAMAGE;

	//�G�t�F�N�g��`�悷����W
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

	//�ϐ�
	std::unique_ptr<Block> mpBlock[BLOCK_MAXNUM];

	//�|�C���^�ۑ��p�ϐ�
	EnemyManager* mpEnemyManager;

public:
	//�֐�
		//�R���X�g���N�^
	BlockManager();
		//�f�X�g���N�^
	~BlockManager();
		//������
	void Initialize(EnemyManager* pEnemyManager);
		//�X�V
	void Update();
		//�ǐ���
	void CreateBlock
		(const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& scale);
		//�`��
	void Draw();
		//�I������
	void Finalize();


	//�G�̓����蔻�����
	void RoolNormalEnemyChackHit(DetectNormalEnemy* pEnemy);
	void RoolSubordinateEnemyChackHit(DetectSubordinateEnemy* pEnemy);
	void RoolBossEnemyChackHit(DetectBossEnemy* pEnemy);

	//�T���v���u���b�N�ƃu���b�N�̓����蔻��
	void ChackHitSampleBlockBlock(PreparingBlock* pPreparingBlock, Player* pPlayer);

	//�u���b�N�ƃv���C���[�̓����蔻��
	void ChackhitPlayerBlock(Player* pPlayer);

	//�u���b�N�Ƌ��̓����蔻��
	void ChackBulletBlock(Bullet* pBullet);

};