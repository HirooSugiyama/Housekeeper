/*
数字が浮く表現を行うクラス
作成者：杉山
作成日：2021/10/22
*/
#pragma once

//基底クラス
#include"../../Common/SpriteNumber/NumberBase.h"

//所持
#include"../Effect/Effect.h"

//前方宣言
class CameraBase;

class FloatNumber3D :public NumberBase
{
private:


	//描画できる最大桁数
	static const int MAX_DIGIT_NUM = 3;

	//数字同士の幅
	static const float NUM_SHIFT;

	//数字の移動速度
	static const float NUM_MOVE_VELOCITY;

	//透明度の変化速度
	static const float NUM_ALPHA_VELOCITY;

	//画像拡大率
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;


	//使用する数字のスプライト画像
	std::unique_ptr<EffectSpriteTexture> mpNumberTexture[MAX_DIGIT_NUM];

	//ポインタ保存用
	CameraBase* mpCamera;

	//始点座標
	DirectX::SimpleMath::Vector3 mInitPosition;

	//使用フラグ
	bool mUseFlag;

public:

	//コンストラクタ
	FloatNumber3D();
	//デストラクタ
	~FloatNumber3D()override;
	//初期化処理
	void Initialize(CameraBase* pCamera);
	//作成処理
	void Create(int num, DirectX::SimpleMath::Vector3 position);
	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	//リセット処理
	void Reset();

private:
	//各変数にほしい番号を入れる
	void CreateNumber(std::vector<int> num);
};

