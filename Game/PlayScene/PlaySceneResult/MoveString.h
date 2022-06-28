/*
指定した場所に移動する文字
作成者：杉山
作成日：2021/10/13
*/
#pragma once




class MoveString
{
private:

	//摩擦 
	static const float FRICTION_FORCE;

	//摩擦を書ける範囲
	static const float FRICTION_RANGE;

	//現在の位置
	DirectX::SimpleMath::Vector2 mPosition;

	//最終位置
	DirectX::SimpleMath::Vector2 mFinishPosition;

	//移動速度
	float mMoveVelocityNum;

	//描画する文字
	const wchar_t* mpDrawString;

	//文字サイズ
	float mStringSize;

	//右側から出てくるフラグ
	bool mRightFlag;

public:

	//コンストラクタ
	MoveString();
	//デストラクタ
	~MoveString();
	//初期化処理
	void Initialize(const DirectX::SimpleMath::Vector2& firstpos,	//最初の座標
		const DirectX::SimpleMath::Vector2& finishpos,				//最終的な座標
		const float& velnum,										//移動速度
		const wchar_t* drawString,									//描画する文字
		const float& stringSize = 1.f								//文字サイズ
		);
	//更新処理
	bool Update();
	//描画処理
	void Draw();

	//指定の位置に強制移動
	void ForcedChangeString() { mPosition = mFinishPosition; }

private:

	//文字の移動
	void StringMove();

};
