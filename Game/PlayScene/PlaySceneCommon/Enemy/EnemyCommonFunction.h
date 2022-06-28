/*
�G�N���X���ʊ֐�
�쐬�ҁF���R
�쐬���F2022/02/26
*/
#pragma once

//�񋓌^�̎g�p
#include"../../Effect/EffectType.h"

//�֐��̎g�p
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"


class EnemyCommonFunction
{
private:

	//�G�t�F�N�g�̏o����������W
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

public:

	//�G�t�F�N�g�ݒ菈��
	static void SetEnemyEffect(const eEffectType& type, const DirectX::SimpleMath::Vector3& position)
	{
		//�G�t�F�N�g�}�l�[�W���[�̎擾
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(type);
		effect->SetPosition(position + EFFECT_SHIFT_POSITION);
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
	}
};