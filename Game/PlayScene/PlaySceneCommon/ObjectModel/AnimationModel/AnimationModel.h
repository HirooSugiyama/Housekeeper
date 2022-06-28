/*
アニメーションモデル
作成者：杉山
作成日：2021/12/26
*/
#pragma once

#include"../ObjectModel.h"

class AnimationModel 
{
private:

	//モデル
	std::unique_ptr<ObjectModel> mpModel;

	//ボーン
	DirectX::ModelBone::TransformArray mBones;

	//アニメーション
	DX::AnimationCMO* mpAnimation;

	//色使用フラグ
	bool mColorFlag;
	//色
	DirectX::SimpleMath::Vector3 mColor;



public:

	//コンストラクタ
	AnimationModel();
	//デストラクタ
	~AnimationModel();
	//初期化処理
	void Initialize(const int& fileKey);
	//更新処理
	void Update(const float& deltaTime);

	//描画処理
	void Draw();

	ObjectModel* GetModel() const { return mpModel.get(); }

	//色使用フラグ
	bool GetColorFlag() { return mColorFlag; }
	//色の設定
	void SetColor(const DirectX::SimpleMath::Vector3& color)
	{
		//色を設定する
		mColor = color;
		mColorFlag = true;
	}
	//フラグを下す
	void DownColorFlag() { mColorFlag = false; }
	//色を取得
	DirectX::SimpleMath::Vector3 GetColor() const { return mColor; }

private:

	//色設定
	void UpdateColor();

};
