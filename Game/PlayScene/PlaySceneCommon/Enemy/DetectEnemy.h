/*
�G�Փˏ������ʏ���
�쐬�ҁF���R
�쐬���F2022/02/20
*/
#pragma once

//�񋓌^�̎g�p
#include "Game/PlayScene/Effect/EffectType.h"

class Administrator;	//�����Ŏg�p

class DetectEnemy
{
private:

	//�|�C���^�ۑ��p�ϐ�
	Administrator* mpAdministrator;

public:
	//�A�N�Z�T
	Administrator* GetAdministrator()const { return mpAdministrator; }
	void SetAdministrator(Administrator* pAdministrator) { mpAdministrator = pAdministrator; }
};
