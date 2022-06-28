/*
空に浮く雲を管理するクラス
作成者：杉山
*/
#pragma once


class Cloud
{
private:
	//雲の初期座標
	static const DirectX::SimpleMath::Vector2 CLOUD_POSITION1;
	static const DirectX::SimpleMath::Vector2 CLOUD_POSITION2;
	static const DirectX::SimpleMath::Vector2 CLOUD_POSITION3;

	//雲の移動速度
	static const float CLOUD_VELOCITY;
	//雲の画面外座標
	static const float CLOUD_OVER_POSITION;
	static const float CLOUD_RESET_POSITION;


	//定数
	//雲の数
	static const int CLOUD_NUM = 3;

	//変数
	//雲の画像
	std::unique_ptr<ObjectTexture> mpClouds[CLOUD_NUM];


public:
	//コンストラクタ
	Cloud();
	//デストラクタ
	~Cloud();

	//初期化
	void Initialize(const int& fileKey);
	//更新処理
	void Update();
	//描画処理
	void Draw();

private:
	//移動処理
	void Move();
	//ワープ処理
	void Warp();

};
