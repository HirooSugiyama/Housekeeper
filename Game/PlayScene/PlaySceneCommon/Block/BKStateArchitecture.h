/*
壁がだんだん立つ動きの壁追加処理
作成者：杉山
作成日：2021/07/21
*/
#pragma once


//基底クラス
#include"BlockKindBase.h"

class BKStateArchitecture :public BlockKindBase
{
private:
	//定数
	//建築速度
	static const float BLOCK_CREATE_SPEED;
	//変数
	//Blockオブジェクトへ保存用のポインタ
	Block* mpBlock;

	//完成した時のY座標
	float mFinishPositionY;

	//埋まった状態のY座標
	float mBeginPositionY;

	//建築スピード
	float mDefenseHouseSpeed;


public:

	//コンストラクタ
	BKStateArchitecture();
	//デストラクタ
	~BKStateArchitecture()override;

	//初期化
	void Initialize(Block* pBlock)override;
	//更新
	bool Update() override;

	//初期化処理(メモリ関係以外)
	void Reset();

private:
	//移動処理
	void DefenseHouse();
	//当たり判定更新処理
	void UpdateCollider();

	//完成前の地面に埋まった状態のY座標を算出
	void CreateBeforePositionY();
	//State移行処理
	bool ChangeStateBlock();

};
