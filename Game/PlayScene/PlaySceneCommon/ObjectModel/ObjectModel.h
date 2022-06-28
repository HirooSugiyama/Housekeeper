/*
モデル描画クラス
作成者：杉山
作成日：2021/04/18
*/
#pragma once

#include"IModel.h"

namespace DirectX
{
	class SpriteBatch;
}

//Todo:省略形は基本使わない。

class ObjectModel:public IModel
{
private:

	//定数

	//初期化時の定数
	static const DirectX::SimpleMath::Vector3 INIT_POSITION;
	//未使用時の定数
	static const DirectX::SimpleMath::Vector3 NOT_USE_POSITION;
	
	//変数

	// コモンステート
	DirectX::CommonStates* mpCommonState;
	// スプライトバッチ
	DirectX::SpriteBatch* mpSpriteBatch;

	//モデル関係
	DirectX::SimpleMath::Matrix mWorld;

	//ビュー行列
	DirectX::SimpleMath::Matrix mView;
	//射影行列
	DirectX::SimpleMath::Matrix mProj;

	//エフェクトファクトリー
	std::unique_ptr<DirectX::IEffectFactory> mFxFactory;
	//モデルの保存先
	DirectX::Model* mModel;

	//座標
	DirectX::SimpleMath::Matrix mPosition;
	//拡大率
	DirectX::SimpleMath::Matrix mScale;
	//回転率
	DirectX::SimpleMath::Matrix mRotX;
	DirectX::SimpleMath::Matrix mRotY;
	DirectX::SimpleMath::Matrix mRotZ;

	//座標Vector版
	DirectX::SimpleMath::Vector3 mPosition3;
	//拡大率Vector版
	DirectX::SimpleMath::Vector3 mScale3;

	//回転率float版
	float mRotAngleX;
	float mRotAngleY;
	float mRotAngleZ;

	//表示フラグ:true	表示	false:非表示
	bool mDrawFlag;

	//モデル使用フラグ
	bool mModelUseFlag;

	//関数
public:
	//コンストラクタ
	ObjectModel();

	//デストラクタ
	~ObjectModel();

	//モデルの指定
	void SetModel(DirectX::Model* model);
	//モデル情報のアクセサ
	DirectX::Model* GetModel()const {return mModel;}

	//座標の指定
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//拡大率の指定
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//回転の指定
	void SetRotationX(const float& rot);
	void SetRotationY(const float& rot);
	void SetRotationZ(const float& rot);


	DirectX::SimpleMath::Matrix GetRotationX()const{return mRotX;}
	DirectX::SimpleMath::Matrix GetRotationY()const{return mRotY;}
	DirectX::SimpleMath::Matrix GetRotationZ()const{return mRotZ;}

	//回転率の角度の取得
	float GetRotAngleX() const{ return mRotAngleX; }
	float GetRotAngleY() const{ return mRotAngleY; }
	float GetRotAngleZ() const{ return mRotAngleZ; }


	//座標の取得
	DirectX::SimpleMath::Vector3  GetPosition()const;
	DirectX::SimpleMath::Vector3*  GetPositionAdress();
	//拡大率の取得
	DirectX::SimpleMath::Vector3  GetScale()const;

	//移動
	void Move(const DirectX::SimpleMath::Vector3& vel);

	//更新処理
	virtual void Update()override {};
	//描画
	virtual void Draw(DirectX::SimpleMath::Matrix* world=nullptr)override;

	//表示非表示の切り替えのアクセサ
	bool GetDrawFlag()const { return mDrawFlag; }
	void SetDrawFlag(const bool& flag) { mDrawFlag = flag; }

	//モデル使用の切り替えフラグ
	bool GetModelUseFlag() const { return mModelUseFlag; }
	void SetModelUseFlag(const bool& flag) { mModelUseFlag = flag; }

	//ワールド座標を計算する
	void CalculationWorldMatrix();

	//ワールド座標のアクセサ
	DirectX::SimpleMath::Matrix GetWorld()const { return mWorld; }
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { mWorld = world; }


};
