/*
敵基底クラス
作成者：杉山
作成日：2022/02/11
*/
#include"pch.h"

#include"IEnemy.h"



//リソースの取得
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"



//モデルの拡大率
//見た目用
const DirectX::SimpleMath::Vector3 IEnemy::ENEMY_SCALE(0.5f, 0.5f, 0.5f);

//モデルに合わせて当たり判定用の拡大率を定める
//プレイヤーはZ方向とY方向に長いので当たり判定をZ方向とY方向に伸ばす
const float IEnemy::ENEMY_COLLIDER_EXTEND_Y = 3.f;
const float IEnemy::ENEMY_COLLIDER_EXTEND_Z = 4.f;


//モデル生成時ミスの修正
const float IEnemy::ENMEY_MODELMISS_FIX_ROT = 180.f;

//エフェクト表示座標
const DirectX::SimpleMath::Vector3 IEnemy::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);



//ダメージ値の描画座標
const DirectX::SimpleMath::Vector3 IEnemy::FLOATNUMBER_DISTANCE_POSITION(0.f, 4.5f, 0.f);


/*===================================
コンストラクタ
引数：なし
===================================*/
IEnemy::IEnemy()
	:mpEnemyModel(),
	mpEnemyShadow(nullptr),
	mpFloatNumber(nullptr),
	mEnemyDamage(0)
{
	mpEnemyModel = std::make_unique<BoxModel>();

	mpEnemyShadow = std::make_unique<Shadow>();
	mpFloatNumber = std::make_unique<FloatNumber3D>();
}

/*===================================
デストラクタ
===================================*/
IEnemy::~IEnemy()
{
}

/*===================================
終了処理(共通)
引数：なし
返り値：なし
===================================*/
void IEnemy::Finalize()
{
	mpEnemyModel.reset();
}


/*=================================
ダメージを与える処理
引数：ダメージ値、HP最大値
返り値：撃破したかどうか(true：撃破)
===================================*/
bool IEnemy::Damage(const int& damagenum, const int& maxHitPoint)
{
	//ダメージを与える
	mEnemyDamage += damagenum;

	if (mEnemyDamage >= maxHitPoint)
	{
		//未使用状態にする
		this->SelfDestroy();
		//エフェクトマネージャーの取得
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::DISAPPEAR);
		effect->SetPosition(IEnemy::GetEnemyModel()->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		return true;
	}
	return false;
}

/*==================================
自身を削除(ポインタなどは消滅しない)
引数：なし
返り値：なし
===================================*/
void IEnemy::SelfDestroy()
{
	//描画中であれば
	if (mpEnemyModel->GetDrawFlag())
	{
		//当たり判定を初期値に
		mpEnemyModel->SetAABBCollider
		(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Vector3::Zero
		);

		//未使用状態にする
		mpEnemyModel->SetModelUseFlag(false);

		//ダメージを初期値に戻す
		mEnemyDamage = 0;
	}
}

/*=================================
エフェクトを作成する
引数；ダメージ値
返り値：なし
===================================*/
void IEnemy::CreateNumberEffect(int damageNum)
{
	mpFloatNumber->Create
	(
		damageNum,
		IEnemy::GetEnemyModel()->GetPosition() +
		FLOATNUMBER_DISTANCE_POSITION
	);
}

/*=================================
エフェクトをリセットする
引数：なし
返り値：なし
===================================*/
void IEnemy::ResetNumberEffect()
{
	mpFloatNumber->Reset();
}

