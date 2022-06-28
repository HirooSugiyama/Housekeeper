/*
汎用処理をまとめたヘッダーファイル
作成者：杉山
作成日：2021/08/31
*/
#pragma once

//3D情報を2D座標で使用する際X,Zを使用するための変換用構造体
struct Vector2XZ
{
	float x;
	float z;

};


struct Utility
{
	//文字フォントサイズ
	//大
	static const float STRING_SIZE_LARGE;
	//中
	static const float STRING_SIZE_MEDIUM;
	//小
	static const float STRING_SIZE_SMALL;
	//極小
	static const float STRING_SIZE_MINIMUM;

	//文字バッファーサイズ
	static const size_t BUFFER_SIZE;
	

	//例外数字
	static const int EXCEPTION_NUM;

	//拡大率を半分にする
	static const int SCALE_HALF;

	//直角
	static const float RIGHT_ANGLE;

	//最終クリアステージ保存用ファイルパス
	static const wchar_t* NEXT_STAGE_NUM_FILEPATH;

	//スプライト画像移動
	static const int SHIFT_SPRITE_TEXTURE;

	//フィールド範囲
	static const float FIELD_MAX_SIZE_X;
	static const float FIELD_MIN_SIZE_X;
	static const float FIELD_MAX_SIZE_Z;
	static const float FIELD_MIN_SIZE_Z;

	//文字を描画する関数
	static void DrawString
	(
		const int& drawNum= EXCEPTION_NUM,
		const DirectX::SimpleMath::Vector2& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		const DirectX::FXMVECTOR& stringColor= DirectX::Colors::White,
		const float& stringSize= STRING_SIZE_LARGE,
		const int& secondNum=EXCEPTION_NUM
	);
	static void DrawString
	(
		wchar_t const* string=L"none",
		const DirectX::SimpleMath::Vector2& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		const DirectX::FXMVECTOR& stringColor= DirectX::Colors::White,
		const float& stringSize= STRING_SIZE_LARGE
	);


	//ファイル未展開エラー
	static void FileError(const std::string& filePath);
	static void FileError(const wchar_t* filePath);

};
