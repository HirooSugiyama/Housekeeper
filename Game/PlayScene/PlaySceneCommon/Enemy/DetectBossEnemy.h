/*
ボス敵衝突判定
作成者：杉山
作成日：2022/02/20
*/
#pragma once

//基底クラス
#include"DetectEnemy.h"

//前方宣言
class BossEnemy;	//所持
class Block;			//引数で使用
class Player;			//引数で使用
class BulletManager;	//引数で使用

class DetectBossEnemy : public DetectEnemy
{
private:

	//ボス敵のスコア
	static const int BOSS_ENEMY_SCORE;

	//配下敵ポインタ保存配列
	BossEnemy* mpChackColliderBossEnemy;

public:

	//コンストラクタ
	DetectBossEnemy();
	//デストラクタ
	~DetectBossEnemy();


	//敵の回数分だけ当たり判定を回す処理
	bool RoolBulletManagerChackhitBossEnemy(BulletManager* pBulletManager);


	//ブロックとボス敵の当たり判定
	void ChackHitBlocklBossEnemy(Block* pBlock);

	//プレイヤーとボス敵の当たり判定
	bool ChackHitPlayerBossEnemy(Player* pPlayer);
	bool ChackHitNormalAttackPlayerBossEnemy(Player* pPlayer);	//プレイヤー攻撃時の判定

	//柵と敵の当たり判定
	void ChackHitWallBossEnemy(AABB* pWallCollider);

	//ボス範囲とプレイヤーの衝突判定
	void ChackHitPlayerBossEnemyArea(Player* pPlayer);

	//アクセサ
	void ResetChackColliderEnemy() { mpChackColliderBossEnemy = nullptr; }
	void SetChackColliderEnemy(BossEnemy* pEnemy)
	{
		mpChackColliderBossEnemy = pEnemy;
	}

};
