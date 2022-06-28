/*
敵ダメージState　～反動～
作成者：杉山
作成日：2022/02/09
*/
#pragma once

//基底クラス
#include"EnemyDamageStateBase.h"


class EnemyDamageStateKnockBack :public EnemyDamageStateBase
{
private:


	//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//拡大率(当たり判定)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;


	//移動速度
	static const float ENEMY_MOVE_SPEED;

	//速度減少率
	static const float ENEMY_MOVE_SPEED_DECREASE;

	//速度最小値
	static const float ENEMY_MIN_VELOCITY;

	//移動ベクトルを小さくする
	static const float ENEMY_MOVE_VELOCITY_SMALL;

	//移動ベクトルを反転させる
	static const float ENEMY_MOVE_VELOCITY_REVERSE;

	//移動ベクトル保存用変数
	DirectX::SimpleMath::Vector3 mMoveVec;



public:

	//コンストラクタ
	EnemyDamageStateKnockBack();
	//デストラクタ
	~EnemyDamageStateKnockBack();
	//初期化処理
	 void Initialize(Enemy* pEnemy, EnemyMainStateDamage* pEnemyMainState)override;
	//リセット処理
	 void Reset()override;
	//更新処理
	 void Update()override;
	//描画処理
	void Draw()override;

	//移動ベクトルの取得
	void SetMoveVector(const DirectX::SimpleMath::Vector3& movevec);

	//移動ベクトルをスケーリング
	void MoveVectorScaling();

private:

	//Vector3のうちの絶対値が最も大きい値を返す関数
	float Vector3Max(const DirectX::SimpleMath::Vector3& num);


};
