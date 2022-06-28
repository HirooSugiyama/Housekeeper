/*
3D座標に2D画像を描画する汎用クラス
(使用例：エフェクトなど)
作成者：杉山
作成日：2021/09/02
*/
#pragma once

#include "Libraries/DirectXTK/Inc/Effects.h"



namespace DirectX
{
	class SpriteBatch;
}
class EffectSpriteTexture
{
private:

	//定数============================
	static const float UV_POSITION_MAX;



	//変数============================

	//座標
	DirectX::SimpleMath::Vector3 mPosition;
	//拡大率
	DirectX::SimpleMath::Vector2 mScale;
	//保存用スプライトバッチ
	DirectX::SpriteBatch* mpSpriteBatch;

	//スプライトタイマー
	int mSpriteTimer;
	//タイマー(固定値)
	int mConstTimer;
	//スプライトタイマー稼働フラグ
	bool mSpriteFlag;
	//行数
	int mLineMaxNum;//行最大数
	int mLineNum;	//現在の行数

	//横分割数の保存
	int mHorizontalCutNum;
	//現在の場所
	int mWidthNum;
	//増加量
	float mWidthIncreaseNum;	//横幅
	float mHeightIncreaseNum;	//縦幅




	//スプライト切り取り単位
	DirectX::SimpleMath::Vector2 mSpriteSrc;

	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

	// プリミティブバッチ 
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> mpPrimitiveBatch;

	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;



	//座標関係(板ポリゴン)
	DirectX::SimpleMath::Matrix mWorld;
	DirectX::SimpleMath::Vector3  mCamera;

	//繰り返しフラグ
	bool mLoopFlag;

	//透明度
	float mAlpha;


	//関数============================

public:


	//コンストラクタ	
	EffectSpriteTexture(const int& linenum = 1,							//画像初期行数						
		const DirectX::SimpleMath::Vector3& position = { 0.f,0.f,0.f },	//表示座標						
		const DirectX::SimpleMath::Vector2& scale = { 1.f,1.f });		//表示拡大率									


	//デストラクタ
	~EffectSpriteTexture();

	//画像の指定
	void SetFileName(const wchar_t* filepath);
	void SetTexture(ID3D11ShaderResourceView* texture);

	//初期化
	void Initialize();

	//更新処理
	void Update();

	//スプライトタイマーの設定
	void SetConstTimer(int timer) { mConstTimer = timer; }

	//描画
	void ExtendDraw();

	//終了処理
	void Finalize();


	//カメラ座標の保存
	void SetCameraEyePosition(DirectX::SimpleMath::Vector3 eyePosition)
	{
		mCamera = eyePosition;
	}


	//アクセサ

	//座標のアクセサ
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { mPosition = position; }
	DirectX::SimpleMath::Vector3 GetPosition()const { return mPosition; }

	//拡大率のアクセサ
	void SetScale(DirectX::SimpleMath::Vector2 scale) { mScale = scale; }
	DirectX::SimpleMath::Vector2 GetScale()const { return mScale; }


	//スプライト周回フラグのアクセサ
	bool GetSpriteFlag() const { return mSpriteFlag; }
	bool* GetSpriteFlagAddress() { return &mSpriteFlag; }
	void SetSpriteFlag(bool flag) { mSpriteFlag = flag; }
	//スプライト位置のアクセサ
	void SetWidthNum(int num) { mWidthNum = num; }
	int GetWidthNum() const { return mWidthNum; }


	//横分割数のアクセサ
	int GetHorizontalCutNum() const { return mHorizontalCutNum; }
	void SetHorizontalCutNum(int num)
	{
		mHorizontalCutNum = num;

		//１/分割数で増加量が求められる(再設定)
		mWidthIncreaseNum = 1.f / static_cast<float>(mHorizontalCutNum);
	};


	//画像情報を取得する
	ID3D11ShaderResourceView* GetTexture() const { return mTexture.Get(); }

	//スプライトのタイマー値を取得する
	int GetConstTimer()const { return mConstTimer; }

	//繰り返し用フラグのアクセサ
	void SetLoopFlag(bool flag) { mLoopFlag = flag; }

	//透明度のアクセサ
	void SetAlpha(float alpha) { mAlpha = alpha; }
};