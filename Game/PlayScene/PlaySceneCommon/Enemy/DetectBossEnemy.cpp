/*
配下敵衝突判定
作成者：杉山
作成日：2022/02/20
*/
#include"pch.h"

#include"DetectBossEnemy.h"

//前方宣言
//所持
#include"BossEnemy.h"

//当たり判定
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Player/ActionStateAttackEnemy.h"
#include"../Bullet/BulletManager.h"

//関数の使用
#include"Game/PlayScene/PlaySceneCommon/Administrator/Administrator.h"
#include"EnemyCommonFunction.h"


//配下敵のスコア
const int DetectBossEnemy::BOSS_ENEMY_SCORE = 100;

/*===================================
コンストラクタ
引数：なし
===================================*/
DetectBossEnemy::DetectBossEnemy()
	:
	mpChackColliderBossEnemy()
{
}

/*===================================
デストラクタ
===================================*/
DetectBossEnemy::~DetectBossEnemy()
{
}

/*=======================================================================================================
敵の回数分だけ当たり判定を回す処理(ボス敵)
引数：弾管理クラスのアドレス
返り値：撃破フラグ
========================================================================================================*/
bool DetectBossEnemy::RoolBulletManagerChackhitBossEnemy(BulletManager* pBulletManager)
{
	//ボスを使用していないときは処理を通さない
	if (!mpChackColliderBossEnemy->GetUseFlag())return false;

	//撃破した数だけ増加させる
	bool breakflag = pBulletManager->ChackHitBulletBossEnemy(mpChackColliderBossEnemy);

	//スコア増加
	if (breakflag)
	{
		DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(BOSS_ENEMY_SCORE);
	}

	return breakflag;
}

/*==================================================
ブロックとボス敵の衝突判定
引数：ブロックのアドレス
返り値：なし
====================================================*/
void DetectBossEnemy::ChackHitBlocklBossEnemy(Block* pBlock)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//衝突判定
	if (pC.Intersect(pBlock->GetBoxModel()->GetAABBCollider(),
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//ブロックを破壊する
		pBlock->SelfDestroy();

		//エフェクトの設定
		EnemyCommonFunction::SetEnemyEffect(eEffectType::DESTROY, pBlock->GetBoxModel()->GetPosition());
	}
}

/*==================================================
プレイヤーとボス敵の衝突判定
引数：プレイヤーのアドレス
返り値：衝突フラグ
====================================================*/
bool DetectBossEnemy::ChackHitPlayerBossEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//未使用時は処理をしない
	if (mpChackColliderBossEnemy == nullptr)return false;

	//プレイヤーがダメージ状態なら処理をしない
	if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) return false;

	//衝突判定
	if (pC.Intersect(pPlayer->GetPlayerCollider(),
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//プレイヤーにダメージを与える
		pPlayer->ChangeStateDamage();

		return true;
	}

	return false;
}

/*==================================================
弱攻撃状態のプレイヤーとボス敵の衝突判定
引数：プレイヤーのアドレス
返り値：撃破フラグ
====================================================*/
bool DetectBossEnemy::ChackHitNormalAttackPlayerBossEnemy(Player* pPlayer)
{
	Collider& pC = Collider::GetColliderInstance();

	//選択肢にnullが入る可能性があるためチェックする
	if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)return false;
	if (mpChackColliderBossEnemy == nullptr)return false;

	//もしプレイヤーが弱攻撃状態でないならば通らない
	if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)return false;

	//回避状態の場合も攻撃を受けない
	if (mpChackColliderBossEnemy->GetStateMove()->GetMoveState() == BossEnemyMoveState::ESCAPE)return false;

	//当たっていたら処理をする
	if (pC.Intersect(
		pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider()))
	{
		//弱攻撃のダメージを与える
		int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

		bool breakjuge = mpChackColliderBossEnemy->Damage(damageNum, mpChackColliderBossEnemy->GetEnemyHP());

		//逃走状態とする
		mpChackColliderBossEnemy->GetStateMove()->ChangeStateEscape();

		//エフェクトを設定する
		EnemyCommonFunction::SetEnemyEffect(eEffectType::SLASH, mpChackColliderBossEnemy->GetEnemyModel()->GetPosition());

		//もし敵を倒していたら
		if (breakjuge)
		{
			//スコアを増やして
			DetectEnemy::GetAdministrator()->DirectAcceserScore()->SetScoreUp(BOSS_ENEMY_SCORE);

			return true;
		}

	}
	return false;
}

/*==================================================
柵とボス敵の衝突判定
引数：柵の衝突判定アドレス
返り値：なし
====================================================*/
void DetectBossEnemy::ChackHitWallBossEnemy(AABB* pWallCollider)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//未使用時は処理をしない
	if (mpChackColliderBossEnemy == nullptr)return;

	//当たっていたら処理をする
	if (pC.Intersect(
		mpChackColliderBossEnemy->GetEnemyModel()->GetAABBCollider(),	//敵の当たり判定
		pWallCollider))										//地上オブジェクトの当たり判定
	{
		//Todo:停止させる
		DirectX::SimpleMath::Vector3 shiftPosition = mpChackColliderBossEnemy->GetEnemyModel()->GetPosition();
		shiftPosition.x = pWallCollider->mMin.x;
		mpChackColliderBossEnemy->GetEnemyModel()->SetPosition(shiftPosition);
	}
}

/*===================================
ボス範囲とプレイヤーの衝突判定
引数：プレイヤーのアドレス
返り値：なし
===================================*/
void DetectBossEnemy::ChackHitPlayerBossEnemyArea(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//未使用時は処理をしない
	if (mpChackColliderBossEnemy == nullptr)return;

	//移動状態以外なら処理をしない
	if (mpChackColliderBossEnemy->GetState() != BossEnemyMainState::MOVE)return;

	//衝突判定
	if (pC.Intersect(
		mpChackColliderBossEnemy->GetPlayerRecognitionRangeCollider(),
		pPlayer->GetPlayerCollider()))
	{

		//配下敵生成処理へ
		mpChackColliderBossEnemy->ChangeStateCreate();

		//生成フラグが立っていなかったら建てる
		if (!mpChackColliderBossEnemy->GetActiveFlag())
		{
			mpChackColliderBossEnemy->SetActiveFlag(true);
		}
	}
}
