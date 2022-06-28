/*
フェード
作成者：杉山
作成日：2021/12/21
*/
#pragma once

class Fade
{
private:
	//全開時
	static const float FULL_OPEN;
	static const float FULL_CLOSE;


	//ピクセルシェーダに渡す定数バッファの構造体
	struct cbChangeEveryFrame
	{
		float alpha;						//アルファ値
		float aspectRatio;					//アスペクト比
		DirectX::SimpleMath::Vector2 dummy;	//パディングデータ(2バイト分)
	};

	//定数バッファ関連
	cbChangeEveryFrame mcbChangeEveryFrame;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mCbBuffer;

	//2Dテクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mTextureBuffer;

	//シェーダ―リソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;

	//オープンまたはクローズするまでのワイプ時間
	float mInterval;

	//割合(0～1)：0の場合閉じている
	float mRate;

	//オープンフラグ:trueの場合オープン
	bool mFlagOpen;


	//ピクセルシェーダ関連
	Microsoft::WRL::ComPtr<ID3DBlob> mpBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mpPixelShader;

public:

	//コンストラクタ
	Fade(float interval = 1.f, float rate = 1.f);
	//デストラクタ
	~Fade();
	//初期化処理
	void Initialize();
	//更新処理
	bool Update(float elaspedTime);
	//描画処理
	void Draw();

	//アクセサ
	void SetOpen()
	{
		mFlagOpen = true; 
	}
	void SetClose()
	{
		mFlagOpen = false; 
	}
	bool GetFlagOpen() const { return mFlagOpen; }
};
