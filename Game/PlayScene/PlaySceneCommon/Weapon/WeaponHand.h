/*
弱攻撃クラス
作成者：杉山
作成日：2021/09/14
*/
#pragma once

//所持
#include"../Player/Player.h"
#include"../ObjectModel/SphereModel.h"
#include"../Player/Animation/NormalAttackAnim.h"


//現在の状態を管理する
enum class eHandState
{
	STAND_BY,
	ATTACK,
	COOL_TIME,
};

class WeaponHand
{
private:


	//プレイヤーの座標から攻撃判定までの距離
	static const DirectX::SimpleMath::Vector3 ATTACKSTATE_PLAYER_DISTANCE_POSITION;

	//当たり判定の拡大率
	static const DirectX::SimpleMath::Vector3 ATTACKSTATE_COLLIRDEMODEL_SCALE;
	static const float ATTACKSTATE_COLLIRDE_SCALE;

	//攻撃最大フレーム数
	static const int ATTACKSTATE_MAX_ATTACK_FRAME;
	//反動最大フレーム数
	static const int ATTACKSTATE_MAX_RECOIL_FRAME;

	//敵への1回の攻撃のダメージ値
	static const int ATTACKSTATE_HAND_DAMAGE;

	//アニメーションの座標を少し上げる値
	static const float ATTACK_STATE_SHIFT_ANIMATION;


	//攻撃判定を含んだオブジェクト
	std::unique_ptr<SphereModel> mpWeapon;

	//アニメーションモデル管理クラス
	std::unique_ptr<NormalAttackAnim> mpAnim;

	//保存用変数
	Player* mpPlayer;

	//表示ワールド座標
	DirectX::SimpleMath::Matrix mWorld;

	//攻撃判定フラグ
	eHandState mAttackFlag;
	//攻撃フレーム計測
	int mAttackFrameCountNum;

	//アニメーションフラグ
	bool mAnimationFlag;

	//攻撃座標
	DirectX::SimpleMath::Vector3 mColliderPosition;

public:

	//コンストラクタ
	WeaponHand();
	//デストラクタ
	~WeaponHand();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();

	//描画処理
	void Draw();

	//ポインタの保存
	void SetPlayerPointer(Player* pPlayer) { mpPlayer=pPlayer; }

	//当たり判定を返す処理
	SphereModel* GetCollider()const { return mpWeapon.get(); }

	//現在の状態を管理するフラグのアクセサ
	void SetAttackFlag(const eHandState& flag) { mAttackFlag = flag; }
	eHandState GetAttackFlag() const { return mAttackFlag; }

	//ダメージ値を返す関数
	int GetDamage() const { return ATTACKSTATE_HAND_DAMAGE; }

	//当たり判定の作成
	DirectX::SimpleMath::Vector3 GetColliderPosition()const { return mColliderPosition; }

	//当たり判定を設定
	void SetCollider(const bool& flag = false);

private:
	//攻撃判定稼働時間
	void AttackFrameCount();

	//リセット処理
	void Reset();
	
};
