/*
壁がだんだん立つ動きの壁追加処理
作成者：杉山
作成日：2021/07/21
*/
#include"pch.h"
#include "BKStateArchitecture.h"



//関数内を閲覧のため必要
#include"Block.h"
#include"../../PlaySceneCommon/ObjectModel/BoxModel.h"




//定数
//建築速度
const float BKStateArchitecture::BLOCK_CREATE_SPEED = 0.005f;

/*====================
コンストラクタ
引数：なし
======================*/
BKStateArchitecture::BKStateArchitecture()
	:BlockKindBase()
	, mpBlock(nullptr)
	, mFinishPositionY(0.f)
	, mBeginPositionY(0.f)
	, mDefenseHouseSpeed(0.f)
{
}

/*======================
デストラクタ
======================*/
BKStateArchitecture::~BKStateArchitecture()
{
}

/*======================
初期化処理
引数：Blockのポインタ
返り値：なし
======================*/
void BKStateArchitecture::Initialize(Block* pBlock)
{
	//ポインタを保存する
	mpBlock = pBlock;
}

/*======================
更新処理
引数：なし
返り値：変更フラグ
======================*/
bool BKStateArchitecture::Update()
{
	//移動処理
	this->DefenseHouse();

	//当たり判定の更新
	this->UpdateCollider();

	//State移行処理
	return this->ChangeStateBlock();
}

/*==============================
初期化処理(メモリ関係以外)
引数：なし
返り値：なし
================================*/
void BKStateArchitecture::Reset()
{
	//建築スピードを設定
	mDefenseHouseSpeed = BLOCK_CREATE_SPEED;

	//壁のサイズから最初のY地点を算出する関数
	this->CreateBeforePositionY();
}

/*======================
移動処理:private
引数：なし
返り値：なし
======================*/
void BKStateArchitecture::DefenseHouse()
{
	//変数宣言
	DirectX::SimpleMath::Vector3 vel;
	//移動量設定
	vel.y = mDefenseHouseSpeed;
	//モデルを動かす
	mpBlock->GetBoxModel()->Move(vel);
}

/*============================
当たり判定更新処理:private
引数：なし
返り値：なし
============================*/
void BKStateArchitecture::UpdateCollider()	
{
	/*当たり判定の更新*/
	//ここでは保存してないためモデルから呼び出す。
	DirectX::SimpleMath::Vector3 modelPosition, modelScale;
	modelPosition = mpBlock->GetBoxModel()->GetPosition();
	modelScale = mpBlock->GetBoxModel()->GetScale();

	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpBlock->GetBoxModel()->ReturnHalfSize(modelScale);
	//設定
	mpBlock->GetBoxModel()->SetAABBCollider(modelPosition - halfsize, modelPosition + halfsize);
}

/*==============================================================
完成前の地面に埋まった状態のY座標を算出:private
引数：なし
返り値：なし
==============================================================*/
void BKStateArchitecture::CreateBeforePositionY()
{
	//建築済み座標を取得
	mFinishPositionY = mpBlock->GetBoxModel()->GetPosition().y;

	//拡大率などから建築前座標を算出
	mBeginPositionY = mFinishPositionY- (mFinishPositionY);

	//実際に代入し更新処理でせり上がらせる。
	DirectX::SimpleMath::Vector3 blockPosition = mpBlock->GetBoxModel()->GetPosition();
	blockPosition.y = mBeginPositionY;
	mpBlock->GetBoxModel()->SetPosition(blockPosition);

}

/*========================================================
State変更処理:private
引数：なし
返り値：変更フラグ(座標に応じてStateを切り替える)
========================================================*/
bool BKStateArchitecture::ChangeStateBlock()
{
	if (mFinishPositionY <= mpBlock->GetBoxModel()->GetPosition().y)
	{
		return true;
	}
	return false;
}
