/*
特に特別な処理を持たない壁クラス
作成者：杉山
作成日：2021/06/21
*/
#pragma once

//基底クラス
#include"BlockKindBase.h"


class BKStateNormal:public BlockKindBase
{
private:
	//変数
	//Blockオブジェクトへ保存用のポインタ
	Block* mpBlock;

public:
	//コンストラクタ
	BKStateNormal()
		:BlockKindBase()
		, mpBlock(nullptr)
	{}
	//デストラクタ
	~BKStateNormal()=default;
	//初期化
	void Initialize(Block* pBlock) override
	{
		mpBlock = pBlock;
	
	}
	//更新
	bool Update()override { return false; }

	//初期化処理(メモリ関係以外)
	void Reset() {}
};