/*
プレイヤーの通常攻撃アニメーションモデルを管理するクラス
作成者：杉山
作成日：2021/09/05
*/
#pragma once

//所持
#include"../../ObjectModel/ObjectModel.h"

class NormalAttackAnim
{

private:

	//Sin値拡大率
	static const float SIN_SCLAE;
	//アニメーションの速度
	static const float ANIM_VELOCITY;
	//アニメーションの加速度
	static const float ANIM_ACCEL;
	//アニメーション最大値
	static const float ANIM_MAX_NUM;

	//アニメーションモデル
	std::unique_ptr<ObjectModel> mpAnimModel;

	//sin値管理用変数
	float mSinNum;

	//速度
	float mVelocity;

	//アニメ―ションを描画するワールド座標
	DirectX::SimpleMath::Matrix mWorld;

public:


	//コンストラクタ
	NormalAttackAnim();
	//デストラクタ
	~NormalAttackAnim();
	//初期化
	void Initialize();
	//リセット処理
	void Reset();
	//更新
	bool Update(const DirectX::SimpleMath::Matrix& playerAttackmat);

	//描画
	void Draw();
};