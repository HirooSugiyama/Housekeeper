/*
敵基底クラス
作成者：杉山
作成日：2022/02/11
*/
#pragma once

//所持
#include "Game/PlayScene/PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../Shadow.h"
#include"../../PlaySceneDefence/FloatNumber3D.h"

class CameraBase;

class IEnemy
{
private:

	//拡大率
	static const DirectX::SimpleMath::Vector3 ENEMY_SCALE;
	//モデルに合わせて当たり判定用の拡大率を定める
	static const float ENEMY_COLLIDER_EXTEND_Y;
	static const float ENEMY_COLLIDER_EXTEND_Z;
	//モデル生成時ミスの修正
	static const float ENMEY_MODELMISS_FIX_ROT;


	//エフェクト表示座標
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;


	//ダメージ値の描画座標
	static const DirectX::SimpleMath::Vector3 FLOATNUMBER_DISTANCE_POSITION;

	//モデル描画クラス
	std::unique_ptr<BoxModel> mpEnemyModel;

	//影
	std::unique_ptr<Shadow> mpEnemyShadow;

	//数字エフェクト
	std::unique_ptr<FloatNumber3D> mpFloatNumber;

	//現在のHP
	int mEnemyDamage;

public:

	//コンストラクタ
	IEnemy();
	//デストラクタ
	virtual ~IEnemy();
	//初期化処理
	virtual void Initialize(const DirectX::SimpleMath::Vector3& position) = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Draw() = 0;
	//終了処理
	void Finalize();

	//ダメージを与える処理
	bool Damage(const int& damagenum, const int& maxHitPoint);

	//自身を削除する。
	void SelfDestroy();

	//エフェクトを作成する
	void CreateNumberEffect(int damageNum);
	//エフェクトをリセットする
	void ResetNumberEffect();


	//共通の状態変更処理
	virtual void ChangeStateCreateBefore() = 0;
	virtual void ChangeStateDisappearance() = 0;
	virtual void ChangeStateMove() = 0;

	//アクセサ
	//カメラポインタの保存
	void SaveCameraPointer(CameraBase* camera) { mpFloatNumber->Initialize(camera); }

	BoxModel* GetEnemyModel()const { return mpEnemyModel.get(); }
	//影のアクセサ
	Shadow* GetShadow()const { return mpEnemyShadow.get(); }
	FloatNumber3D* GetFloatNumber3D()const { return mpFloatNumber.get(); }

	//定数のアクセサ
	DirectX::SimpleMath::Vector3 GetEnemyScale()const { return ENEMY_SCALE; }
	float GetEnemyColliderExtendY() const { return ENEMY_COLLIDER_EXTEND_Y; }
	float GetEnemyColliderExtendZ() const { return ENEMY_COLLIDER_EXTEND_Z; }
	float GetEnemyModelMissFixRotation() const { return ENMEY_MODELMISS_FIX_ROT; }

	//現在のHPのアクセサ
	int GetEnemyDamage()const { return mEnemyDamage; }

	//敵のHPのアクセサ
	virtual int GetEnemyHP() = 0;
};
