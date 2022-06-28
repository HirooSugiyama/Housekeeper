/*
武器の説明文管理クラス
作成者：杉山
作成日：2021/12/08
*/
#pragma once

//列挙型の使用
#include"../PlaySceneCommon/Weapon/WeaponeType.h"
//所持
#include"../../Common/ObjectSpriteTexture.h"

class WeaponExplanatory
{
private:
	//文字列の描画座標
	static const DirectX::SimpleMath::Vector2 STRING_POSITION;
	//文字列の拡大率
	static const DirectX::SimpleMath::Vector2 STRING_SCALE;


	//文字列の色座標
	static const DirectX::SimpleMath::Color STRING_COLOR;
	//各種武器の説明文
	static const RECT STRING_RENGE;

	
	//描画する文字列(画像)
	std::unique_ptr<ObjectSpriteTexture> mpExplanatory;
	

public:

	//コンストラクタ
	WeaponExplanatory();
	//デストラクタ
	~WeaponExplanatory();
	//初期化処理
	void Initialize();
	//更新処理
	void Update(const eWeaponType& type);
	//描画処理
	void Draw();
};
