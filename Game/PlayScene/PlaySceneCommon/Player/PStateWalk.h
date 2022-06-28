/*
プレイヤーの状態分けステートパターン：移動状態
作成者：杉山
作成日：2021/06/15
*/
#pragma once
#include"PlayerStateBase.h"

//所持
#include"../ObjectModel/ObjectSpriteModel.h"
#include"../ObjectModel/AnimationModel/AnimationModel.h"

class PStateWalk:public PlayerStateBase
{
private:

	//定数 	
	//壁の範囲
	static const float MAX_POSITION_X;
	static const float MAX_POSITION_Z;
	static const float MIN_POSITION_Z;
	//スプライトの数
	static const int WALKPLAYER_SPRITE_NUM;
	//スプライトのサイクル
	static const int WALKPLAYER_SPRITE_CYCLE;


	//プレイヤーの移動量(X)
	static const float PLAYER_MOVE_VELOCITY_X;
	//プレイヤーの移動量(Y)
	static const float PLAYER_MOVE_VELOCITY_Y;
	//プレイヤーの移動量(Z)
	static const float PLAYER_MOVE_VELOCITY_Z;

	//移動量の増加量
	static const float PLAYER_MOVE_INCREASE_VELOCITY;


	//プレイヤーの向く向き

	//左
	static const int PLAYER_CHARACTER_ANGLE_L;
	//右		
	static const int PLAYER_CHARACTER_ANGLE_R;
	//上	
	static const int PLAYER_CHARACTER_ANGLE_U;
	//下		
	static const int PLAYER_CHARACTER_ANGLE_D;
	//左上
	static const int PLAYER_CHARACTER_ANGLE_LU;
	//右上	   
	static const int PLAYER_CHARACTER_ANGLE_RU;
	//左下	   
	static const int PLAYER_CHARACTER_ANGLE_LD;
	//右下	  
	static const int PLAYER_CHARACTER_ANGLE_RD;

	//モデル角度修正
	static const float PLAYER_FIX_MODEL_ROTATION_Y;

	//変数
	//Playerオブジェクトへ保存用のポインタ
	Player* mpPlayer;

	//スプライトモデル
	std::unique_ptr<AnimationModel> mpWalkAnimationModel;

	//実際のプレイヤーの速度
	DirectX::SimpleMath::Vector3 mActualPlayerVelocity;

	//移動後のプレイヤーの当たり判定
	std::unique_ptr<AABB> mpDestinationPlayerCollider;

	//地上オブジェクトに当たっていないか判定するフラグ
	bool mGroundObjectXHitFlag;
	bool mGroundObjectZHitFlag;
	//ブロックに当たっていないか判定するフラグ
	bool mBlockHitFlag;

public:
	//関数
	//コンストラクタ
	PStateWalk();
	//初期化処理
	void Initialize(Player* pPlayer)override;
	//State開始時の初期化処理
	void Reset()override {};
	//更新処理
	void Update()override;
	//描画処理
	void Draw()override;

	//移動ベクトルを算出
	DirectX::SimpleMath::Vector3 CalculationMoveVelocity();


	//移動後のプレイヤーの当たり判定を返す(移動はしない)
	AABB* GetDestinationPlayerCollider();

	//地上オブジェクトに当たっていないか判定するフラグのアクセサ	
	void SetGroundObjectXHitFlag(const bool& flag) { mGroundObjectXHitFlag = flag; }
	void SetGroundObjectZHitFlag(const bool& flag) { mGroundObjectZHitFlag = flag; }
	//ブロックに当たっていないか判定するフラグのアクセサ
	void SetBlockHitFlag(const bool& flag) { mBlockHitFlag = flag; }

private:
	//全てのオブジェクトに当たっていない場合のみ処理を通す関数
	void AllObjectHit();

	//移動処理
	void Move();

	//座標を取得しスプライトモデルに代入する
	void SetSpriteModelPosition();
	
	//移動量を加速度的に増加させる
	void ConstantAcceleration();


	//使用する加速度をすべて初期化
	void AllActualPlayerVelocityInit();
};