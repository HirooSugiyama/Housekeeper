/*
�{�X�G��{State�@�`�ړ��`
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

//���N���X
#include"EnemyMainStateBase.h"

#include"EnemyMoveState/EnemyMoveStateRotation.h"
#include"EnemyMoveState/EnemyMoveStateWalk.h"
#include"EnemyMoveState/EnemyMoveStateWallAttack.h"

//�񋓌^�̎g�p
#include"EnemyMainState.h"


//�O���錾
class EnemyMoveStateBase;	//���State
class Block;				//����
class SubordinateEnemy;

class BossEnemyMainStateCreate : public EnemyMainStateBase
{
private:
	//��]���x
	static const float ROTATION_VELOCITY;

	//�z���\�ԍ�
	static const int ARRAY_REPRESENTATIVE_NUM;

public:

	//�R���X�g���N�^
	BossEnemyMainStateCreate();
	//�f�X�g���N�^
	~BossEnemyMainStateCreate();
	//����������
	void Initialize(IEnemy* pEnemy)override;
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;

	//���g������A�h���X��Ԃ�
	SubordinateEnemy* GetSubordinateEnemyAddress();

};
