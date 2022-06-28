/*
�z���G�ړ�State�@���N���X
�쐬�ҁF���R
�쐬���F2022/02/14
*/
#pragma once

//�O���錾
class SubordinateEnemyMainStateMove;
class IEnemy;

class SubordinateEnemyMoveStateBase
{
private:

	//���L�҂̃|�C���^
	SubordinateEnemyMainStateMove* mpEnemyMainState;
	IEnemy* mpEnemy;

public:

	//�R���X�g���N�^
	SubordinateEnemyMoveStateBase();
	//�f�X�g���N�^
	virtual ~SubordinateEnemyMoveStateBase();
	//����������
	virtual void Initialize(IEnemy* mpEnemy, SubordinateEnemyMainStateMove* mpEnemyMainState) = 0;
	//�X�V����
	virtual void Update() = 0;

	//�A�N�Z�T
	SubordinateEnemyMainStateMove* GetEnemyMainState() const { return mpEnemyMainState; }
	void SetEnemyMainState(SubordinateEnemyMainStateMove* pEnemyMainState) { mpEnemyMainState = pEnemyMainState; }

	IEnemy* GetEnemy() const { return mpEnemy; }
	void SetEnemy(IEnemy* pEnemy) { mpEnemy = pEnemy; }

};
