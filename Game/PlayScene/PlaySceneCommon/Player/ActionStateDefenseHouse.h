/*
プレイヤーの行動状態分けステートパターン
作成者：杉山
作成日：2021/09/14
*/
#pragma once


//基底クラス
#include"ActionStateBase.h"

//列挙型の使用
#include"Defense/eDefenseActionState.h"

//所持
#include"Defense/DefenseActionBlockCreate.h"


class BlockManager;					//ポインタ保存用
class PreparingBlock;				//ポインタ保存用
class PreparingScarecrow;			//ポインタ保存用

class ActionStateDefenseHouse :public ActionStateBase
{
private:

	//壁建処理
	std::unique_ptr<DefenseActionBlockCreate> mpBlockCreate;

	//現在の状態
	eDefenseActionState mDefenseHouseState;

public:

	//コンストラクタ
	ActionStateDefenseHouse();
	//デストラクタ
	~ActionStateDefenseHouse();
	//初期化処理
	void Initialize(Player * pPlayer);

	//ポインタ保存処理
	void SetCreateBlockPointer(PreparingBlock* pPreparingBlock,
		BlockManager* pBlockManager);


	//更新処理
	void Update();
	//State開始時の初期化処理
	void Reset();
	//描画処理
	void Draw();

	//壁建処理へのアクセス権
	DefenseActionBlockCreate* GetBlockCreate() const {return mpBlockCreate.get();	}

	//現在の状態
	eDefenseActionState GetDefenseHouseState()const {return mDefenseHouseState;}
};
