/*
�e�Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/09/17
*/
#pragma once

//�񋓌^�̎g�p
#include"../Weapon/WeaponeType.h"
#include"../../Effect/EffectType.h"

//����
#include"Bullet.h"
#include"BulletType.h"


//�O���錾
class Bullet;			//����
class BulletType;		//����
class Enemy;			//�����蔻��̈����Ŏg�p
class BossEnemy;		//�����蔻��̈����Ŏg�p
class SubordinateEnemy;	//�����蔻��̈����Ŏg�p
class BlockManager;		//�����蔻��̈����Ŏg�p
class CameraBase;		//�|�C���^�ۑ��p
class Player;			//�|�C���^�ۑ��p
class EnemyManager;		//�|�C���^�ۑ��p

class BulletStateBoomerang;	//����

class BulletManager
{
private:

	//�e�̍ő吔
	static const int BULLET_MAX_NUM = 50;

	//�ő�͈�
	static const float BULLET_MAX_POSITION_Z;

	//�C���^�[�o���v���I���p�������p�萔
	static const int BULLET_INTERVAL_FINISH_NUM;

	//�e
	std::unique_ptr<Bullet> mpBullet[BULLET_MAX_NUM];

	//�e���Ǘ��N���X
	std::unique_ptr<BulletType> mpBulletType;

	//�e���˃C���^�[�o������t���O
	bool mBulletShotIntervalFlag;

	//���݂̃C���^�[�o���p�^�C�}�[
	int mIntervalTimer;

	//���݂̕���̒e�̎��
	eWeaponType mWeaponType;

	//�|�C���^�ۑ��p�ϐ�
	CameraBase* mpCamera;

	//�u�[�������̂ݗB��̕��̂��ߊǗ��N���X�ŊǗ�
	std::unique_ptr<BulletStateBoomerang> mpBoomerangBullet;

	//�|�C���^�ۑ��p�ϐ�
	EnemyManager* mpEnemyManager;

public:

	//�R���X�g���N�^
	BulletManager();
	//�f�X�g���N�^
	~BulletManager();
	//����������
	void Initialize(CameraBase* pCamera, Player* pPlayer, EnemyManager* pEnemyManager);

	//�e��������
	bool Create(const DirectX::SimpleMath::Vector3& position);

	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//�C���^�[�o���p�^�C�}�[�����Z�b�g����
	void ResetIntervalTimer() { mIntervalTimer = 0; }

	//�����̃A�N�Z�T
	void SetWeaponType(const eWeaponType& type) { mWeaponType = type; }

	//�e�ƓG�̏Փ˔�������
	int ChackHitBulletEnemy(Enemy* pEnemy);

	//�e�ƃ{�X�G�̏Փ˔�������
	int ChackHitBulletBossEnemy(BossEnemy* pEnemy);

	//�e�Ɣz���G�̏Փ˔�������
	int ChackHitBulletSubordinateEnemy(SubordinateEnemy* pEnemy);

	//�v���C���[�ƒe�̏Փ˔���
	void ChackHitBulletPlayer(Player* pPlayer);

	//�u���b�N�Ƃ̏Փ˔�����񂷊֐�
	void RoolChackHitBlock(BlockManager* pBlockManager);

	//�u�[�������̃|�C���^��n��
	BulletStateBoomerang* GetBoomerangBullet() const { return mpBoomerangBullet.get(); }

	//�e�̊Ǘ����̃A�N�Z�T
	BulletType* GetBulletType() const { return mpBulletType.get(); }

private:

	//�͈͊O����
	void OutOfRange();

	//�C���^�[�o���v��
	bool MeasureInterval();

};
