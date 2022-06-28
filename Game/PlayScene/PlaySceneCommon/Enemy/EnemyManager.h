/*
�G�Ǘ��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once


#include"../../Effect/EffectType.h"

//����
#include"EnemyCall.h"
#include"Enemy.h"
#include"BossEnemy.h"
#include"SubordinateEnemy.h"

//�O���錾
class Block;				//�����蔻��
class Player;				//�����蔻��
class Protecter;			//�����蔻��
class Administrator;		//�|�C���^(����)
class DangerousLine;		//�|�C���^(����)
class GroundObjectManager;	//�����蔻��
class BulletManager;		//�����蔻��
struct AABB;				//�����蔻��
class EffectSpriteTexture;	//����
class CameraBase;			//�|�C���^(����)

class EnemyManager
{
private:

	//�萔
	//�����T�C�Y
	static const int ENEMY_INIT_SIZE;
	
	//���g�p�̓G�̏o�����W
	static const DirectX::SimpleMath::Vector3 NOT_SET_ENEMY_POSITION;

	//�����g�嗦
	static const DirectX::SimpleMath::Vector3 ENEMY_INIT_SCALE;

	//BOSS�������̒ʏ�G��������
	static const int ENEMY_ADDITIONAL_CAPACITY;

	//�z���G��
	static const int SUBORDINATE_ENEMY_NUM = 20;

	//�z���G�����͈�
	static const int SUBORDINATE_ENEMY_CREATE_RANGE;

	//�{�X�G�̔z���G������
	static const int SUBORDINATE_ENEMY_CREATE_NUM;

	//�{�X�G�̒ʏ�G������
	static const int NORNAML_ENEMY_CREATE_NUM;

	//�z���G�̐�����
	static const int SUBORDINATE_ENEMY_ARIVE_NUM;

	//�{�X�G�̒ʏ�G�������̃t�F�[�Y�ԍ�
	static const int NORMAL_ENEMY_CREATE_PHASE;


	//�ϐ�
	std::vector<std::unique_ptr<Enemy>> mpEnemy;
	std::unique_ptr<BossEnemy> mpBossEnemy;
	std::unique_ptr<SubordinateEnemy> mpSubordinateEnemy[SUBORDINATE_ENEMY_NUM];

	//�Ăяo���N���X
	std::unique_ptr<EnemyCall> mpEnemyCall;

	//�|�C���^�ۑ�
	Administrator* mpAdministrator;

	//�G�̍ő�o�����W
	int mMaxEnemySpawnPositionZ;

	//�ǂݍ��ރt�@�C����
	std::string mLoadEnemyFileName;

	//���݂̃t�F�[�Y�ԍ�
	int mNowPhaseNum;

	//�ő�t�F�[�Y��
	int mMaxPhaseNum;

	//���݂̓G�̌��j��
	int mNowEnemyBreakNum;

	//�{�X�g�p�t���O
	bool mBossEnemyUseFlag;

public:
	//�֐�
	//�R���X�g���N�^
	EnemyManager();
	//�f�X�g���N�^
	~EnemyManager();
	//������
	void Initialize(CameraBase* camera, Administrator* pAdministrator, Player* pPlayer);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�I������
	void Finalize();

	//���Z�b�g����
	void Reset();

	//�ǂݍ��ރt�@�C�����̎擾
	void SetLoadEnemyFileName(const std::string & filename) { mLoadEnemyFileName = filename; }

	//�ǂݍ��ރt�@�C�������쐬
	std::string CreateLoadEnemyFileName(const std::string & stagenum);

	//�t�F�[�Y�ԍ��̎擾
	void SetNowPhaseNum(const int& phasenumber) { mNowPhaseNum = phasenumber; }
	void SetMaxPhaseNum(const int& phasenumber) { mMaxPhaseNum = phasenumber; }

	//�S�Ă̓G�����S�������Ƃ��m�F����t���O
	bool AllEnemyDeathFlag();

	//�G���j���̃A�N�Z�T
	int GetBreakEnemyNum()const { return mNowEnemyBreakNum; }
	void AddBreakEnemyNum(const int& addNum) { mNowEnemyBreakNum += addNum; }

	//�G�̍ő吔�̃A�N�Z�T
	int GetMaxEnemyNum()const
	{
		if (mpBossEnemy->GetUseFlag())
		{
			return NORMAL_ENEMY_CREATE_PHASE;
		}
		return static_cast<int>(mpEnemy.size()); 
	}

	//�c���Ă���G����Ăɔ��j������
	void ExplosionSimultaneousEnemy();

	//�u���b�N�Փ˃t���O
	void ResetEnemyBlockHitFlag();

	//�{�X�g�p�t���O�̃A�N�Z�T
	bool GetBossEnemyUseFlag() const { return mBossEnemyUseFlag; }

	//�z���G����
	void CreateSubordinateEnemy();

	//�g�p���̃|�C���^�̃A�N�Z�T
	std::vector<Enemy*> GetUseNormalEnemyVector();
	BossEnemy* GetBossEnemyVector();
	std::vector<SubordinateEnemy*> GetUseSubordinateEnemyVector();

private:

	//�t�@�C����������擾����
	void LoadFile(std::string filepath);

	//�{�X�G��������
	bool CreateBoss();

	//���W����
	DirectX::SimpleMath::Vector3 CreatePosition(const DirectX::SimpleMath::Vector3& position);

	//�z���G�̐������`�F�b�N
	int ChackSubordinateEnemyUseNum();
};
