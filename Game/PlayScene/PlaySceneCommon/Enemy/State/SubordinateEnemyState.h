/*
�z���G�̏�Ԃ�\���񋓌^
�쐬�ҁF���R
�쐬���F2022/02/13
*/
#pragma once


enum class SubordinateEnemyMainState
{
	CREATE_BEFORE,	//�����O
	MOVE,			//�ړ�
	DISAPPEARANCE,	//����
};

enum class SubordinateEnemyMoveState
{
	STAND,	//����
	WALK	//�������
};