/*
�{�X�G�p�̏��State���Ǘ�����񋓌^�Q
�쐬�ҁF���R
�쐬���F2022/02/12
*/
#pragma once

enum class BossEnemyMainState
{
	CREATE_BEFORE,	//�����O
	MOVE,			//�ړ�
	ATTACK,			//�U��
	CREATE,			//����
	DISAPPEARANCE,	//����
};

enum class BossEnemyMoveState
{
	WALK,	//���s
	ESCAPE,	//����
	STAND,	//����
};
