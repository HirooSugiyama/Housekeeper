/*
敵クラス共通関数
作成者：杉山
作成日：2022/02/26
*/
#pragma once

//列挙型の使用
#include"../../Effect/EffectType.h"

//関数の使用
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"


class EnemyCommonFunction
{
private:

	//エフェクトの出現させる座標
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

public:

	//エフェクト設定処理
	static void SetEnemyEffect(const eEffectType& type, const DirectX::SimpleMath::Vector3& position)
	{
		//エフェクトマネージャーの取得
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(type);
		effect->SetPosition(position + EFFECT_SHIFT_POSITION);
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
	}
};