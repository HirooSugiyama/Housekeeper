/*
障害物管理クラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once



//定数の使用
#include"WallConstant.h"

//所持
#include"Wall.h"

//当たり判定用
class Player;
class PreparingBlock;
class DetectNormalEnemy;
class DetectSubordinateEnemy;
class DetectBossEnemy;

class WallManager
{
private:

	enum class eWallPosition
	{
		LEFT_WALL,
		RIGHT_WALL,
	};

	//定数
		//壁の数
	static const int WALL_MAX_NUM = 2;

	//変数
		//壁
	std::unique_ptr<Wall> mpWall[WALL_MAX_NUM];

public:
	//関数
		//コンストラクタ
	WallManager();
	//デストラクタ
	~WallManager();
	//初期化
	void Initialize();
	//描画
	void Draw();

	//敵との当たり判定を回す処理
	void RoolNormalEnemyChackHit(DetectNormalEnemy* pDetectNormalEnemy);
	void RoolBossEnemyChackHit(DetectBossEnemy* pDetectBossEnemy);

};