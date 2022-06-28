/*
配下敵衝突判定
作成者：杉山
作成日：2022/02/20
*/
#pragma once

//基底クラス
#include"DetectEnemy.h"

//前方宣言
class SubordinateEnemy;	//所持
class Block;			//引数で使用
class Player;			//引数で使用
class BulletManager;			//引数で使用

class DetectSubordinateEnemy: public DetectEnemy
{
private:

	//配下敵のスコア
	static const int SUBORDINATE_ENEMY_SCORE;

	//配下敵ポインタ保存配列
	std::vector<SubordinateEnemy*> mpChackColliderSubordinateEnemy;
	//簡略化用変数
	int mEnemySize;


public:

	//コンストラクタ
	DetectSubordinateEnemy();
	//デストラクタ
	~DetectSubordinateEnemy();

	//敵の回数分だけ当たり判定を回す処理
	void RoolBulletManagerChackhitSubordinateEnemy(BulletManager* pBulletManager);

	//ブロックと配下敵の当たり判定
	void ChackHitBlocklSubordinateEnemy(Block* pBlock);

	//プレイヤーと配下敵の当たり判定
	bool ChackHitPlayerSubordinateEnemy(Player* pPlayer);
	void ChackHitNormalAttackPlayerSubordinateEnemy(Player* pPlayer);	//プレイヤー攻撃時の判定

	//アクセサ
	void ResetChackColliderEnemy() { mpChackColliderSubordinateEnemy.resize(0); }
	void SetChackColliderEnemy(std::vector<SubordinateEnemy*> pEnemy)
	{
		mpChackColliderSubordinateEnemy = pEnemy;
		mEnemySize = static_cast<int>(pEnemy.size());
	}
private:
	//使用している配下敵全てを停止させる
	void AllSubordinateEnemyStop();
};
