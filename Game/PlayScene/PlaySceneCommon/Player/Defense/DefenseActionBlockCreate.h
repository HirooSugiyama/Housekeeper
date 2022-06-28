/*
壁を建てる動作
作成者：杉山
作成日：2021/11/13
*/
#pragma once

class Player;					//ポインタ保存用
class BlockManager;				//ポインタ保存用
class PreparingBlock;			//ポインタ保存用

class DefenseActionBlockCreate
{
private:

	//ブロックの費用
	static const int BLOCK_COST;

	//ポインタ保存用変数
	Player* mpPlayer;
	PreparingBlock* mpPreparingBlock;
	BlockManager* mpBlockManager;


	//ブロックの重なりフラグ
	bool mOverLappingFlag;

	//判定用ラインと見本用ブロックの重なりフラグ(true→重なっている)
	bool mGridLineFlag;


public:

	//コンストラクタ
	DefenseActionBlockCreate();
	//デストラクタ
	~DefenseActionBlockCreate();
	//初期化処理
	void Initialize(Player* pPlayer);


	//ポインタ保存処理
	void SetPointer(PreparingBlock* pPreparingBlock, BlockManager* pBlockManager);


	//ブロック生成
	void Create();

	//描画処理
	void Draw();

	//壁生成フラグのアクセサ
	void SetmOverLappingFlag(const bool& flag) { mOverLappingFlag = flag; }

	//判定用ラインと見本用ブロックの重なりフラグのアクセサ
	void SetGridLineFlag(const bool& flag) { mGridLineFlag = flag; }
};
