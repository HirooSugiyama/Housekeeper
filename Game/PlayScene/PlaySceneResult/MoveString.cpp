/*
指定した場所に移動する文字
作成者：杉山
作成日：2021/10/13
*/
#include"pch.h"

#include"MoveString.h"

//摩擦 
const float MoveString::FRICTION_FORCE = 0.97f;

//摩擦を書ける範囲
const float MoveString::FRICTION_RANGE = 100.f;

/*===============================================
コンストラクタ
引数：なし
===============================================*/
MoveString::MoveString()
	:
	mPosition(),
	mFinishPosition(),
	mMoveVelocityNum(),
	mpDrawString(),
	mStringSize(),
	mRightFlag(false)	//基本は左側から
{
}

/*===================================
デストラクタ
===================================*/
MoveString::~MoveString()
{
}

/*===================================
初期化処理
引数：	最初の座標、最後の座標、
		移動速度、描画する文字
		文字サイズ
返り値：なし
===================================*/
void MoveString::Initialize(const DirectX::SimpleMath::Vector2& firstpos,		//最初の座標
							const DirectX::SimpleMath::Vector2& finishpos,		//最終的な座標
							const float& velnum,								//移動速度
							const wchar_t* drawString,							//描画する文字
							const float& stringSize)							//文字サイズ				
{
	//各引数の保存
	mPosition = firstpos;
	mFinishPosition = finishpos;
	mMoveVelocityNum = velnum;
	mpDrawString = drawString;
	mStringSize = stringSize;

	//もし最終座標より初期座標が大きかったら
	if (mFinishPosition.x < mPosition.x)
	{
		//文字を右側から出現させる
		mRightFlag = true;
	}
}

/*===================================
更新処理
引数：なし
返り値：完了したかしていないか
===================================*/
bool MoveString::Update()
{
	//右側からの出現の場合
	if (mRightFlag)
	{
		//現在の座標が目的地につくまで
		if (mPosition.x >= mFinishPosition.x && mPosition.y >= mFinishPosition.y)
		{
			//文字の移動
			this->StringMove();
		}
		else
		{
			return true;
		}
	}
	else
	{
		//現在の座標が目的地につくまで
		if (mPosition.x <= mFinishPosition.x && mPosition.y <= mFinishPosition.y)
		{
			//文字の移動
			this->StringMove();
		}
		else
		{
			return true;
		}
	}
	return false;
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void MoveString::Draw()
{
	//動く値の描画
	Utility::DrawString
	(
		mpDrawString,
		mPosition,
		DirectX::Colors::White,
		mStringSize
	);
}

/*===================================
文字の移動：private
引数：なし
返り値：なし
===================================*/
void MoveString::StringMove()
{
	//右側からの出現の場合
	if (mRightFlag)
	{
		//ある程度の範囲に入ったら摩擦を起こす
		if (mPosition.x - FRICTION_RANGE <= mFinishPosition.x)
		{
			mMoveVelocityNum *= FRICTION_FORCE;
		}

		//移動処理
		mPosition.x -= mMoveVelocityNum;
	}
	//左側からの出現の場合
	else
	{
		//ある程度の範囲に入ったら摩擦を起こす
		if (mPosition.x + FRICTION_RANGE >= mFinishPosition.x)
		{
			mMoveVelocityNum *= FRICTION_FORCE;
		}

		//移動処理
		mPosition.x += mMoveVelocityNum;
	}

	
}




