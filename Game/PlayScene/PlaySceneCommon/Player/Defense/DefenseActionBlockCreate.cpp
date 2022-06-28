/*
壁建て処理
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"

#include"DefenseActionBlockCreate.h"


//関数の使用
#include"Game/UI/MoneyTexture.h"
#include"Game/UI/UI.h"

//前方宣言
#include"../../../PlaySceneCommon/Administrator/Administrator.h"
#include"../../../PlaySceneDefence/PreparingBlock.h"
#include"../../../PlaySceneCommon/Block/BlockManager.h"
#include"../Player.h"


//関数内部の呼び出しで使用
#include"../../../PlaySceneCommon/ObjectModel/BoxModel.h"

//所持金の取得
#include"Game/Money/Money.h"


//ブロックの費用
const int DefenseActionBlockCreate::BLOCK_COST = 10;

/*=====================================
コンストラクタ
引数：なし
=====================================*/
DefenseActionBlockCreate::DefenseActionBlockCreate()
	:
	mpPlayer(nullptr),
	mpPreparingBlock(nullptr),
	mpBlockManager(nullptr),
	mOverLappingFlag(false),
	mGridLineFlag(false)
{
}

/*=====================================
デストラクタ
=====================================*/
DefenseActionBlockCreate::~DefenseActionBlockCreate()
{
}

/*=====================================
初期化処理
引数：プレイヤーのポインタ
返り値：なし
=====================================*/
void DefenseActionBlockCreate::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}


/*=====================================
ポインタ保存関数
引数：見本ブロックのポインタ
		ブロック管理クラスのポインタ
返り値：なし
=====================================*/
void DefenseActionBlockCreate::SetPointer(
		PreparingBlock* pPreparingBlock,
		BlockManager* pBlockManager)
{
	mpPreparingBlock = pPreparingBlock;
	mpBlockManager = pBlockManager;
}

/*===================================
ブロック生成処理
引数：なし
返り値：なし
===================================*/
void DefenseActionBlockCreate::Create()
{
	//ラインの点上ではないなら処理を通さない
	if (mGridLineFlag == false)
	{
		return;
	}

	//見本ブロックと立っているブロックが重なっていたら処理を通す
	if (mOverLappingFlag == false)
	{

		// キー入力情報を取得する
		KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
		GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

		//所持金取得
		auto& pM = Money::GetMoneyInstance();

		//ブロック建て判定取得
		bool Createflag = false;
		if (pM.GetMoney() >= BLOCK_COST)
		{
			Createflag = true;
		}


		if (pKey->ActionDefenseHouse()|| pGamePad->ActionPlayer())//キー入力が行われたら
		{
			//資材数が必要数を超していたら
			if (Createflag)
			{
				pM.ReduceMoney(BLOCK_COST);

				//ブロックを生成する
				mpBlockManager->CreateBlock
				(mpPreparingBlock->GetBoxModel()->GetPosition(),
					mpPreparingBlock->GetBoxModel()->GetScale());


				mpPlayer->GetUIPointer()->CreateMoneyEffect(BLOCK_COST);
			}
		}
	}
}

/*=====================================
描画処理
引数：なし
返り値：なし
=====================================*/
void DefenseActionBlockCreate::Draw()
{
	//やられ状態以外の場合はブロックを表示する
	if (mpPlayer->GetPlayerState() != ePlayerState::DAMAGE)
	{
		mpPreparingBlock->Draw();
	}
}
