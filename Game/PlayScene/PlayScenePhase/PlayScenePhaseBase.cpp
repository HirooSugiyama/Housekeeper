/*
プレイフェーズ内部のフェーズ分け基底クラス
作成者：杉山
作成日：2021/06/16
*/
#include "pch.h"
#include "PlayScenePhaseBase.h"



//前方宣言
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"
#include"../PlaySceneCommon/Block/BlockManager.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/GridLine/GridLineManager.h"
#include"../PlaySceneCommon/Weapon/WeaponManager.h"
#include"../PlaySceneCommon/Wall/WallManager.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/Ground.h"
#include"../PlaySceneCommon/Protecter.h"
#include"../PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"



/*=================================
コンストラクタ
引数：なし
=================================*/
PlayScenePhaseBase::PlayScenePhaseBase()
	:
	mpAdministrator(nullptr),
	mpBlockManager(nullptr),
	mpEnemyManager(nullptr),
	mpGridLineManager(nullptr),
	mpWeaponManager(nullptr),
	mpWallManager(nullptr),
	mpPlayer(nullptr),
	mpGround(nullptr),
	mpProtecter(nullptr),
	mpGroundObjectManager(nullptr),
	mpBulletManager(nullptr),
	mpUI(nullptr)
{
}

/*=================================
共通で使用するポインタの保存
=================================*/
void PlayScenePhaseBase::SaveCommonPointer(
	Administrator* pAdministrator, 
	BlockManager* pBlockManager, 
	EnemyManager* pEnemyManager, 
	GridLineManager* pGridLineManager,
	WeaponManager* pWeaponManager, 
	WallManager* pWallManager, 
	Player* pPlayer, 
	Ground* pGround, 
	Protecter* pProtecter,
	GroundObjectManager* pGroundObjectManager,
	BulletManager* pBulletManager,
	UI* pUI)
{
	mpAdministrator = pAdministrator; 
	mpBlockManager = pBlockManager;
	mpEnemyManager = pEnemyManager;
	mpGridLineManager = pGridLineManager;
	mpWeaponManager = pWeaponManager;
	mpWallManager = pWallManager;
	mpPlayer = pPlayer;
	mpGround = pGround;
	mpProtecter = pProtecter;
	mpGroundObjectManager = pGroundObjectManager;
	mpBulletManager = pBulletManager;
	mpUI = pUI;
}
