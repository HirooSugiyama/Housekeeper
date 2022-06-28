/*
現在のブロックの状態の処理を行う基底クラス
作成者：杉山
作成日：2021/06/21
*/
#pragma once

class Block;

class BlockKindBase
{
public:
	//コンストラクタ
	BlockKindBase() {};
	//デストラクタ
	virtual ~BlockKindBase() = default;
	//初期化
	virtual void Initialize(Block* pBlock) = 0;
	//更新
	virtual bool Update() = 0;

	//初期化処理(メモリ関係以外)
	virtual void Reset() = 0;

};