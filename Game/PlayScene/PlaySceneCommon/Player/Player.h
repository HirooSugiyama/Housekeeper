/*
プレイヤークラス
作成者：杉山
作成日：2021/10/21
*/

#pragma once

//列挙型の使用
#include"PlayerActionState.h"


//実際に所持
#include"../ObjectModel/BoxModel.h"
#include"../ObjectModel/AnimationModel/AnimationModel.h"
#include"../Shadow.h"

//移動状態State
enum class ePlayerState
{
	STAND,	//立ち状態(標準)
	WALK,	//移動状態
	DAMAGE,	//ダメージ状態

};


//前方宣言
class PStateStand;				//状態分け
class PStateWalk;				//状態分け
class PStateDamage;				//状態分け
class PlayerStateBase;			//状態分け基底クラス

class ActionStateDefenseHouse;	//行動状態分け
class ActionStateAttackEnemy;	//行動状態分け
class ActionStateBase;			//行動状態基底クラス



class BlockManager;				//ポインタ保存用
class PreparingBlock;			//ポインタ保存用
class Administrator;			//ポインタ保存用
class ScarecrowManager;			//ポインタ保存用
class PreparingScarecrow;		//ポインタ保存用
class UI;						//ポインタ保存用

class Player
{
private:
	//定数
	//初期座標
	static const DirectX::SimpleMath::Vector3 PLYAER_INIT_POSITION;

	//モデルの拡大率
		//見た目用
	static const DirectX::SimpleMath::Vector3 PLAYER_MODEL_SCALE;

	//プレイヤーは縦長なので当たり判定を縦に伸ばす
	static const float PLAYER_COLLIDER_EXTEND_Y;
	//実際のプレイヤーのZ値はとても小さいので小さくする
	static const float PLAYER_COLLIDER_EXTEND_Z;

	//シールドパニッシュ用ゲージ必要量
	static const int BLOCKBREAK_USE_GAUGENUM;
	//シールドパニッシュ用拡大率
	static const DirectX::SimpleMath::Vector3 BLOCKBREAK_SCALE;


	//変数
	//モデル描画クラス
	std::unique_ptr<AnimationModel> mpAnimationPlayerModel;
	AABB mPlayerCollider;

	//ブロック周りの処理をするクラス
	PreparingBlock* mpPreparingBlock;

	//生成済みポインタ保存変数
	BlockManager* mpBlockManager;
	Administrator* mpAdministrator;
	UI* mpUI;
	PreparingScarecrow* mpPreparingScarecrow;

	//状態分けステートパターン
	std::unique_ptr<PStateStand> mpStand;
	std::unique_ptr<PStateWalk> mpWalk;
	std::unique_ptr<PStateDamage> mpDamage;
	// 現在の状態
	PlayerStateBase* mpPlayerState;
	ePlayerState mState;


	//行動状態分けステートパターン
	std::unique_ptr<ActionStateDefenseHouse> mpDefenseHouse;
	std::unique_ptr<ActionStateAttackEnemy> mpAttackEnemy;
	//現在の状態
	ActionStateBase* mpPlayerActionState;
	ePlayerActionState mActionState;

	//1フレーム前のプレイヤーの座標
	DirectX::SimpleMath::Vector3 mOneFrameBeforePosition;

	//影
	std::unique_ptr<Shadow> mpPlayerShadow;

	//プレイヤー攻撃用ワールド座標保存用変数
	DirectX::SimpleMath::Matrix mPlayerAttackWorldMatrix;

public:
	//関数
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Initialize(BlockManager* pBlockManager,
		Administrator* pAdministrator,
		PreparingBlock* pPreparingBlock,
		UI* pUI);
	//更新
	void Update();
	//描画
	void Draw();
	//終了処理
	void Finalize();


	//アクセサ関連
	//状態分け
	void ChangeStateStand() { mpPlayerState = (PlayerStateBase*)mpStand.get(); }
	void ChangeStateWalk()	{ mpPlayerState = (PlayerStateBase*)mpWalk.get(); }
	void ChangeStateDamage(){ mpPlayerState = (PlayerStateBase*)mpDamage.get(); }
	
	void SetState(const ePlayerState& state) { mState = state; }
	ePlayerState GetPlayerState()const { return mState; }

	PStateWalk* GetStateWalk()const {return mpWalk.get();}


	void ChangePlayerActionStateDefenseHouse()
	{ 
		mpPlayerActionState = (ActionStateBase*)mpDefenseHouse.get();
		mActionState = ePlayerActionState::BLOCK_CREATE;
	}
	void ChangePlayerActionStateAttackEnemy() 
	{
		mpPlayerActionState = (ActionStateBase*)mpAttackEnemy.get();
		mActionState = ePlayerActionState::ATTACK_ENEMY; 
	}
	void ChangePlayerActionStateStrongWeapon() 
	{
		mpPlayerActionState = (ActionStateBase*)mpAttackEnemy.get();
		mActionState = ePlayerActionState::STRONG_WEWPON; 
	}
	ActionStateBase* GetActionStateBase() const { return mpPlayerActionState; }
	
	ActionStateAttackEnemy* GetAttackEnemyPointer() const { return mpAttackEnemy.get(); }

	void SetActionState(ePlayerActionState const& state) { mActionState = state; }
	ePlayerActionState GetActionState()const { return mActionState; }

	//当たり判定を返す
	ObjectModel* GetPlayerModel()const { return mpAnimationPlayerModel->GetModel(); }
	AABB* GetPlayerCollider() { return &mPlayerCollider; }

	//行動Stateのアクセサ
	ActionStateDefenseHouse* GetDefenseHouse() const { return mpDefenseHouse.get(); }
	ActionStateAttackEnemy* GetAttackEnemy() const { return mpAttackEnemy.get(); }


	//1フレーム前のプレイヤーの座標のアクセサ
	DirectX::SimpleMath::Vector3 GetOneFrameBeforePosition()const { return mOneFrameBeforePosition; }
	void SetOneFrameBeforePosition(const DirectX::SimpleMath::Vector3&position) { mOneFrameBeforePosition = position; }

	//当たり判定の高さの定数のアクセサ
	float GetPlayerColliderExtendY()const { return PLAYER_COLLIDER_EXTEND_Y; }


	//当たり判定更新処理
	void UpdateCollider();

	UI* GetUIPointer()const { return mpUI; }

	//プレイヤーの攻撃用ワールド座標のアクセサ
	DirectX::SimpleMath::Matrix GetPlayerAttackWorldMatrix() const { return mPlayerAttackWorldMatrix; }

	//プレイヤー座標のアドレスのアクセサ
	DirectX::SimpleMath::Vector3* GetPlayerPositionAddress()
	{
		return mpAnimationPlayerModel->GetModel()->GetPositionAdress();
	}

private:

	//行動State変更
	void ChangeAction();

	//攻撃用ワールド座標の計算
	void CalculationAttackMat();

};