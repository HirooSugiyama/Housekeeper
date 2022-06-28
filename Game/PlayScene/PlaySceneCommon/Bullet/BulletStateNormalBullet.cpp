/*
基本的な弾の移動処理
作成者：杉山
作成日：2021/10/16
*/

#include"pch.h"
#include "BulletStateNormalBullet.h"

//前方宣言
#include"Bullet.h"

//関数の使用
#include"../../PlaySceneCommon/ObjectModel/SphereModel.h"

/*==================
コンストラクタ
引数：なし
==================*/
BulletStateNormalBullet::BulletStateNormalBullet()
	:
	BulletStateBase()
{
}

/*=======================================
移動処理
引数：なし
返り値：こちらは未使用(別State先で使用)
=======================================*/
bool BulletStateNormalBullet::Move()
{
	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//座標へ反映
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	return false;
}


/*=================================
弾衝突時の通常敵の処理
引数：なし
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateNormalBullet::HitNormalEnemy(Enemy* pEnemy)
{
	//未使用引数のエラーよけ処理
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}
/*=================================
弾衝突時のボス敵の処理
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateNormalBullet::HitBossEnemy(BossEnemy* pEnemy)
{
	//未使用引数のエラーよけ処理
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}
/*=================================
弾衝突時の配下敵の処理
引数：なし
返り値：エフェクトの種類
===================================*/
eEffectType BulletStateNormalBullet::HitSubordinateEnemy(SubordinateEnemy* pEnemy)
{
	//未使用引数のエラーよけ処理
	UNREFERENCED_PARAMETER(pEnemy);

	return eEffectType::SLASH;
}