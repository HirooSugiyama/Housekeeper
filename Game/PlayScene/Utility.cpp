/*
汎用処理をまとめたファイル
作成者：杉山
作成日：2021/08/31
*/
#include"pch.h"
#include"Utility.h"

//文字フォントサイズ
//大
const float Utility::STRING_SIZE_LARGE = 3.f;
//中
const float Utility::STRING_SIZE_MEDIUM = 2.f;
//小
const float Utility::STRING_SIZE_SMALL = 1.5f;
//極小
const float Utility::STRING_SIZE_MINIMUM = 1.f;


//文字バッファーサイズ
const size_t Utility::BUFFER_SIZE = 32;


//例外数字
const int Utility::EXCEPTION_NUM = -1;

//拡大率を半分にする
const int Utility::SCALE_HALF = 2;

//直角
const float Utility::RIGHT_ANGLE = 90.f;

//最終クリアステージ保存用ファイルパス
const wchar_t* Utility::NEXT_STAGE_NUM_FILEPATH = L"SaveData/FinalClear.csv";

//スプライト画像移動
const int Utility::SHIFT_SPRITE_TEXTURE = 2;

//フィールド範囲
const float Utility::FIELD_MAX_SIZE_X = 19.f;
const float Utility::FIELD_MIN_SIZE_X = -FIELD_MAX_SIZE_X;
const float Utility::FIELD_MAX_SIZE_Z = 11.f;
const float Utility::FIELD_MIN_SIZE_Z = -40.f;

/*==============================
文字列を描画する共通関数
引数：描画する数字
		座標
		色
		文字サイズ
返り値：なし
==============================*/
void Utility::DrawString(const int& drawNum,
						const DirectX::SimpleMath::Vector2& stringPosition,
						const DirectX::FXMVECTOR& stringColor,
						const float& stringSize,
						const int& secondNum)
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	wchar_t buf[32];

	swprintf_s(buf, Utility::BUFFER_SIZE, L" %d", drawNum);
	if (secondNum != EXCEPTION_NUM)
	{
		swprintf_s(buf, Utility::BUFFER_SIZE, L" %d:%d", drawNum, secondNum);
	}

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		buf,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero, 
		stringSize
	);
}

/*==============================
文字列を描画する共通関数
引数：描画する文字列
		座標
		色
		文字サイズ
返り値：なし
==============================*/
void Utility::DrawString(wchar_t const* string,
	const DirectX::SimpleMath::Vector2& stringPosition,
	const DirectX::FXMVECTOR& stringColor,
	const float& stringSize)
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		string,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero,
		stringSize
	);
}


/*==============================
ファイル未展開エラー
引数：ファイルパス
返り値：なし
==============================*/
void Utility::FileError(const std::string& filePath)
{
	//ファイル変換
	std::ifstream ifs(filePath);
	//仮保存用変数
	std::string lineBuf;

	//引き出す
	std::getline(ifs, lineBuf);

	//中身が入っている場合は抜ける
	if (lineBuf != "")
	{
		return;
	}
	else
	{
		throw "Unable to extract file";
	}
}

void Utility::FileError(const wchar_t* filePath)
{
	//ファイル変換
	std::ifstream ifs(filePath);
	//仮保存用変数
	std::string lineBuf;

	//引き出す
	std::getline(ifs, lineBuf);

	//中身が入っている場合は抜ける
	if (lineBuf != "")
	{
		return;
	}
	else
	{
		throw "Unable to extract file";
	}
}
