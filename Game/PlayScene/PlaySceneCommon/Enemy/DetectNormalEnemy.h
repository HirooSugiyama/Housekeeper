/*
通常敵衝突判定
作成者：杉山
作成日：2022/02/20
*/
#pragma once

//基底クラス
#include"DetectEnemy.h"

class Enemy;			//所持
class BulletManager;	//引数で使用
class Block;			//引数で使用
class Player;			//引数で使用
class Protecter;		//引数で使用
class DangerousLine;	//引数で使用

class DetectNormalEnemy :public DetectEnemy
{
private:

	//敵のプレイヤー捕捉範囲
	static const float ENEMY_CAPTURE_RANGE;

	//スコア値
	static const int NORMAL_ENEMY_SCORE;


	//敵ポインタ保存配列
	std::vector<Enemy*> mpChackColliderEnemy;

	//サイズ簡略化変数
	int mEnemySize;

	//ボス使用フラグ
	bool mBossEnemyUseFlag;

public:


	//コンストラクタ
	DetectNormalEnemy();
	//デストラクタ
	~DetectNormalEnemy();

	//敵の回数分だけ当たり判定を回す処理
	int RoolBulletManagerChackhit(BulletManager* pBulletManager);

	//ブロックと敵の当たり判定
	void ChackHitBlocklEnemy(Block* pBlock);

	//プレイヤーと敵の当たり判定
	bool ChackHitPlayerEnemy(Player* pPlayer);
	int ChackHitNormalAttackPlayerEnemy(Player* pPlayer);	//プレイヤー攻撃時の判定

	//拠点と敵の当たり判定
	void ChackHitProtecterEnemy(Protecter* pProtecter);

	//地上オブジェクトと敵の当たり判定
	void ChackHitGroundObjectEnemy(AABB* pObjectCollider);

	//柵と敵の当たり判定
	void ChackHitWallNormalEnemy(AABB* pWallCollider);

	//危険信号ラインと敵の当たり判定
	bool ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine);

	//対象と敵の距離判定
	void ChackDistanceTargetEnemy(const DirectX::SimpleMath::Vector3& position);

	//アクセサ
	void ResetChackColliderEnemy() { mpChackColliderEnemy.resize(0); }
	void SetChackColliderEnemy(std::vector<Enemy*> pEnemy)
	{
		mpChackColliderEnemy = pEnemy;
		mEnemySize = static_cast<int>(pEnemy.size());
	}
	void SetBossUseFlag(const bool& flag) { mBossEnemyUseFlag = flag; }
};
