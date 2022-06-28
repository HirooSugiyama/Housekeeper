/*
障害物管理クラス
作成者：杉山
作成日：2021/10/21
*/
#include<pch.h>
#include "WallManager.h"


//前方宣言
//当たり判定用
#include"../Player/Player.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../Enemy/DetectNormalEnemy.h"
#include"../Enemy/DetectSubordinateEnemy.h"
#include"../Enemy/DetectBossEnemy.h"

//当たり判定で内部閲覧のため使用
#include"../ObjectModel/BoxModel.h"
//移動速度の取得で使用
#include"../ObjectMove.h"

#include"WallConstant.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
WallManager::WallManager()
	:
	mpWall{}
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		mpWall[i] = std::make_unique<Wall>();
	}
}

/*===================================
デストラクタ
===================================*/
WallManager::~WallManager()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WallManager::Initialize()
{
	//変数の宣言
	DirectX::SimpleMath::Vector3 position,scale;

	//左壁
	position.x = WallConstant::WALL_LEFT_POSITION_X;
	position.y = WallConstant::WALL_LEFT_POSITION_Y;
	position.z = WallConstant::WALL_LEFT_POSITION_Z;

	scale.x = WallConstant::WALL_LEFT_SCALE_X;
	scale.y = WallConstant::WALL_LEFT_SCALE_Y;
	scale.z = WallConstant::WALL_LEFT_SCALE_Z;

	mpWall[static_cast<int>(eWallPosition::LEFT_WALL)]->Initialize(position, scale);

	//右壁
	position.x = WallConstant::WALL_RIGHT_POSITION_X;
	position.y = WallConstant::WALL_RIGHT_POSITION_Y;
	position.z = WallConstant::WALL_RIGHT_POSITION_Z;

	scale.x = WallConstant::WALL_RIGHT_SCALE_X;
	scale.y = WallConstant::WALL_RIGHT_SCALE_Y;
	scale.z = WallConstant::WALL_RIGHT_SCALE_Z;
	mpWall[static_cast<int>(eWallPosition::RIGHT_WALL)]->Initialize(position, scale);

}
/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void WallManager::Draw()
{
	for (int i = 0; i < WALL_MAX_NUM; i++) 
	{
		mpWall[i]->Draw();
	}
}

/*===================================
敵との当たり判定を回す処理
引数：敵管理クラスのポインタ
返り値：なし
===================================*/
void WallManager::RoolNormalEnemyChackHit(DetectNormalEnemy* pDetectNormalEnemy)
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		//当たり判定を回す
		pDetectNormalEnemy->ChackHitWallNormalEnemy(mpWall[i]->GetWallModel()->GetAABBCollider());
	}

}
void WallManager::RoolBossEnemyChackHit(DetectBossEnemy* pDetectBossEnemy)
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		//当たり判定を回す
		pDetectBossEnemy->ChackHitWallBossEnemy(mpWall[i]->GetWallModel()->GetAABBCollider());
	}

}
