/*
プレイヤーの行動状態分けステートパターン
作成者：杉山
作成日：2021/09/14
*/

#include"pch.h"
#include "ActionStateDefenseHouse.h"


/*=====================================
コンストラクタ
引数：なし
=====================================*/
ActionStateDefenseHouse::ActionStateDefenseHouse()
	:
	ActionStateBase(),
	mpBlockCreate(nullptr),
	mDefenseHouseState(eDefenseActionState::BLOCK_CREATE)
{
	mpBlockCreate = std::make_unique<DefenseActionBlockCreate>();
}

/*=====================================
デストラクタ
=====================================*/
ActionStateDefenseHouse::~ActionStateDefenseHouse()
{
}

/*=====================================
初期化処理
引数：プレイヤーのポインタ
返り値：なし
=====================================*/
void ActionStateDefenseHouse::Initialize(Player* pPlayer)
{
	//壁建処理の初期化処理
	mpBlockCreate->Initialize(pPlayer);
}


/*====================================
壁建クラスで使用するポインタ保存処理
引数：見本用ブロッククラスのポインタ
		ブロック管理クラスのポインタ
返り値：なし
=====================================*/
void ActionStateDefenseHouse::SetCreateBlockPointer(
		PreparingBlock* pPreparingBlock,
		BlockManager* pBlockManager)
{
	//ポインタを保存する
	mpBlockCreate->SetPointer(pPreparingBlock, pBlockManager);
}


/*=====================================
更新処理
引数：なし
返り値：なし
=====================================*/
void ActionStateDefenseHouse::Update()
{
	//壁建クラスの更新処理
	mpBlockCreate->Create();
}

/*=====================================
State開始時の初期化処理
引数：なし
返り値：なし
=====================================*/
void ActionStateDefenseHouse::Reset()
{

}

/*=====================================
描画処理
引数：なし
返り値：なし
=====================================*/
void ActionStateDefenseHouse::Draw()
{
	//壁建処理の描画処理
	mpBlockCreate->Draw();
}