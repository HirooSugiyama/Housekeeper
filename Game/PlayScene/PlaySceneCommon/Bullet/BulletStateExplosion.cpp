/*
爆発する弾の移動処理
作成者：杉山
作成日：2021/10/16
*/

#include"pch.h"
#include "BulletStateExplosion.h"

//前方宣言
#include"Bullet.h"

//関数の使用
#include"../ObjectModel/SphereModel.h"
#include"../Enemy/Enemy.h"
#include"../Enemy/BossEnemy.h"
#include"../Enemy/SubordinateEnemy.h"

//エフェクトの取得
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//重力定数の使用
#include"../../PlaySceneDefence/Gravity.h"

//重力定数
const float BulletStateExplosion::GRAVITY = Gravity::mGravityConstant;

//初期速度
const float BulletStateExplosion::FIRST_VELOCITY = 0.3f;

//最初の高さ
const float BulletStateExplosion::FIRST_HEIGHT = 1.f;


//エフェクトを出現させる座標
const DirectX::SimpleMath::Vector3 BulletStateExplosion::EFFECT_SHIFT_POSITION(0.f, 2.5f, 0.f);

/*==================
コンストラクタ
引数：なし
==================*/
BulletStateExplosion::BulletStateExplosion()
	:
	BulletStateBase(),
	mBulletVelocity(FIRST_VELOCITY),
	mBulletHeight(FIRST_HEIGHT)
{
}

/*======================================
移動処理
引数：なし
返り値：こちらは未使用(別State先で使用)
=======================================*/
bool BulletStateExplosion::Move()
{
	//もし爆発フラグが立っていたら
	if (BulletStateBase::GetBullet()->GetExplosionFlag())
	{
		//エフェクトを発生させる
		//エフェクトマネージャーの取得
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::BOMB);
		effect->SetPosition(BulletStateBase::GetBullet()->GetBulletModel()->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetScale(effect->GetScale());
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		//未使用状態とする
		this->Reset();
		return true;
	}


	mBulletVelocity -= GRAVITY;
	mBulletHeight += mBulletVelocity;

	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//座標へ反映
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	DirectX::SimpleMath::Vector3 position = BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	position.y = mBulletHeight;

	BulletStateBase::GetBullet()->GetBulletModel()->SetPosition(position);
	

	//地面より下に行ったら
	if (position.y <= 0.f)
	{
		//爆発フラグを建てる
		BulletStateBase::GetBullet()->SetExplosionFlag(true);
		BulletStateBase::GetBullet()->SetDoubleCollider();
	}

	return false;	
}

/*======================================
描画処理
引数：なし
返り値：なし
=======================================*/
void BulletStateExplosion::Draw()
{

}


/*=================================
弾衝突時の通常敵の処理
引数：通常敵のポインタ
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateExplosion::HitNormalEnemy(Enemy* pEnemy)
{
	//衝突判定拡張
	BulletStateBase::GetBullet()->SetDoubleCollider();

	//ノックバックの方向を算出する
	DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetEnemyModel()->GetPosition() -
		BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	knockBackVelocity.y = 0.f;

	//状態をダメージ状態とする
	pEnemy->ChangeStateDamage();
	pEnemy->GetStateDamage()->ChangeStateKnockBack();
	pEnemy->GetStateDamage()->MoveVectorScaling(knockBackVelocity);

	//エフェクトのタイプを設定
	return eEffectType::BOMB;
}
/*=================================
弾衝突時のボス敵の処理
引数：ボス敵のポインタ
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateExplosion::HitBossEnemy(BossEnemy* pEnemy)
{
	//衝突判定拡張
	BulletStateBase::GetBullet()->SetDoubleCollider();

	//ノックバックの方向を算出する
	DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetEnemyModel()->GetPosition() -
		BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	knockBackVelocity.y = 0.f;

	//状態をダメージ状態とする
	pEnemy->ChangeStateMove();
	pEnemy->GetStateMove()->ChangeStateEscape();

	//エフェクトのタイプを設定
	return eEffectType::BOMB;
}
/*=================================
弾衝突時の配下敵の処理
引数：配下敵のポインタ
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateExplosion::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//衝突判定拡張
	BulletStateBase::GetBullet()->SetDoubleCollider();

	//ノックバックの方向を算出する
	DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetEnemyModel()->GetPosition() -
		BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	knockBackVelocity.y = 0.f;

	//エフェクトのタイプを設定
	return eEffectType::BOMB;
}


/*======================================
リセット処理:private
引数：なし
返り値：なし
=======================================*/
void BulletStateExplosion::Reset()
{
	mBulletVelocity = FIRST_VELOCITY;
	mBulletHeight = FIRST_HEIGHT;
}