/*
敵管理クラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once


#include"../../Effect/EffectType.h"

//所持
#include"EnemyCall.h"
#include"Enemy.h"
#include"BossEnemy.h"
#include"SubordinateEnemy.h"

//前方宣言
class Block;				//当たり判定
class Player;				//当たり判定
class Protecter;			//当たり判定
class Administrator;		//ポインタ(引数)
class DangerousLine;		//ポインタ(引数)
class GroundObjectManager;	//当たり判定
class BulletManager;		//当たり判定
struct AABB;				//当たり判定
class EffectSpriteTexture;	//所持
class CameraBase;			//ポインタ(引数)

class EnemyManager
{
private:

	//定数
	//初期サイズ
	static const int ENEMY_INIT_SIZE;
	
	//未使用の敵の出現座標
	static const DirectX::SimpleMath::Vector3 NOT_SET_ENEMY_POSITION;

	//初期拡大率
	static const DirectX::SimpleMath::Vector3 ENEMY_INIT_SCALE;

	//BOSS生成時の通常敵数増加量
	static const int ENEMY_ADDITIONAL_CAPACITY;

	//配下敵数
	static const int SUBORDINATE_ENEMY_NUM = 20;

	//配下敵生成範囲
	static const int SUBORDINATE_ENEMY_CREATE_RANGE;

	//ボス敵の配下敵生成数
	static const int SUBORDINATE_ENEMY_CREATE_NUM;

	//ボス敵の通常敵生成数
	static const int NORNAML_ENEMY_CREATE_NUM;

	//配下敵の生存数
	static const int SUBORDINATE_ENEMY_ARIVE_NUM;

	//ボス敵の通常敵生成時のフェーズ番号
	static const int NORMAL_ENEMY_CREATE_PHASE;


	//変数
	std::vector<std::unique_ptr<Enemy>> mpEnemy;
	std::unique_ptr<BossEnemy> mpBossEnemy;
	std::unique_ptr<SubordinateEnemy> mpSubordinateEnemy[SUBORDINATE_ENEMY_NUM];

	//呼び出しクラス
	std::unique_ptr<EnemyCall> mpEnemyCall;

	//ポインタ保存
	Administrator* mpAdministrator;

	//敵の最大出現座標
	int mMaxEnemySpawnPositionZ;

	//読み込むファイル名
	std::string mLoadEnemyFileName;

	//現在のフェーズ番号
	int mNowPhaseNum;

	//最大フェーズ数
	int mMaxPhaseNum;

	//現在の敵の撃破数
	int mNowEnemyBreakNum;

	//ボス使用フラグ
	bool mBossEnemyUseFlag;

public:
	//関数
	//コンストラクタ
	EnemyManager();
	//デストラクタ
	~EnemyManager();
	//初期化
	void Initialize(CameraBase* camera, Administrator* pAdministrator, Player* pPlayer);
	//更新
	void Update();
	//描画
	void Draw();
	//終了処理
	void Finalize();

	//リセット処理
	void Reset();

	//読み込むファイル名の取得
	void SetLoadEnemyFileName(const std::string & filename) { mLoadEnemyFileName = filename; }

	//読み込むファイル名を作成
	std::string CreateLoadEnemyFileName(const std::string & stagenum);

	//フェーズ番号の取得
	void SetNowPhaseNum(const int& phasenumber) { mNowPhaseNum = phasenumber; }
	void SetMaxPhaseNum(const int& phasenumber) { mMaxPhaseNum = phasenumber; }

	//全ての敵が死亡したことを確認するフラグ
	bool AllEnemyDeathFlag();

	//敵撃破数のアクセサ
	int GetBreakEnemyNum()const { return mNowEnemyBreakNum; }
	void AddBreakEnemyNum(const int& addNum) { mNowEnemyBreakNum += addNum; }

	//敵の最大数のアクセサ
	int GetMaxEnemyNum()const
	{
		if (mpBossEnemy->GetUseFlag())
		{
			return NORMAL_ENEMY_CREATE_PHASE;
		}
		return static_cast<int>(mpEnemy.size()); 
	}

	//残っている敵を一斉に爆破させる
	void ExplosionSimultaneousEnemy();

	//ブロック衝突フラグ
	void ResetEnemyBlockHitFlag();

	//ボス使用フラグのアクセサ
	bool GetBossEnemyUseFlag() const { return mBossEnemyUseFlag; }

	//配下敵生成
	void CreateSubordinateEnemy();

	//使用中のポインタのアクセサ
	std::vector<Enemy*> GetUseNormalEnemyVector();
	BossEnemy* GetBossEnemyVector();
	std::vector<SubordinateEnemy*> GetUseSubordinateEnemyVector();

private:

	//ファイルから情報を取得する
	void LoadFile(std::string filepath);

	//ボス敵生成処理
	bool CreateBoss();

	//座標生成
	DirectX::SimpleMath::Vector3 CreatePosition(const DirectX::SimpleMath::Vector3& position);

	//配下敵の生存数チェック
	int ChackSubordinateEnemyUseNum();
};
