/*
プレイヤーのブロック生成周りの処理
作成者：杉山
作成日：2021/06/18
*/
#pragma once


//所持
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"

//関数内で使用
class GridLineManager;

class PreparingBlock
{
private:

	//定数
	//ブロック生成必要資材数
	static const int BLOCK_CREATE_MONEY_NUM;

	//プレイヤーから少しずらす座標
	static const DirectX::SimpleMath::Vector3 BLOCK_SHIFT_PLAYERPOSITION;

	//円情報の半径
	static const float SAMPLEBLOCK_COLLIDER_RADIUS;

	//ブロックの拡大率
	static const DirectX::SimpleMath::Vector3 SAMPLEBLOCK_SCALE;
	//ブロックの初期座標
	static const DirectX::SimpleMath::Vector3 SAMPLEBLOCK_INIT_POSITION;



	/*移動処理*/
		//見本ブロックの移動量(X)
	static const float SAMPLEBLOCK_MOVE_VELOCITY_X;
	//見本ブロックの移動量(Y)
	static const float SAMPLEBLOCK_MOVE_VELOCITY_Y;
	//見本ブロックの移動量(Z)
	static const float SAMPLEBLOCK_MOVE_VELOCITY_Z;

	//変数
		//配置見本ブロック表示用モデル
	std::unique_ptr<BoxModel> mpSampleModel;
	//判定用ラインとの衝突判定用当たり判定
	std::unique_ptr<Circle> mpCircleCollider;

	//移動フラグ
	bool mMoveFlag;

public:
	//関数
	//コンストラクタ
	PreparingBlock();
	//デストラクタ
	~PreparingBlock();
	//初期化
	void Initialize();
	//更新
	void Update(const DirectX::SimpleMath::Vector3& movevel, GridLineManager* pGridLineMnager);
	//描画
	void Draw();

	//移動処理
	void Move(const DirectX::SimpleMath::Vector3& movevel, GridLineManager* pGridLineMnager);

	//モデルへのアクセサ
	BoxModel* GetBoxModel() const { return mpSampleModel.get(); }

	//衝突判定のアクセサ
	Circle* GetCircleCollider() const { return mpCircleCollider.get(); }

	//移動フラグのアクセサ
	void SetMoveFlag(const bool& flag) { mMoveFlag = flag; }

	//判定用ラインに重なっていないときに処理するブロック資材変更関数
	void ChangeNotUseBlock();

private:
	//資材が足りていないとき処理するブロックの資材変更関数
	void ChangeNotEnoughMat();

	//当たり判定生成処理
	void CircleColliderUpdate();

};