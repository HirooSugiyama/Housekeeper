/*
武器の説明文管理クラス
作成者：杉山
作成日：2021/12/08
*/
#include"pch.h"

#include"WeaponExplanatory.h"

//文字列の描画座標
const DirectX::SimpleMath::Vector2 WeaponExplanatory::STRING_POSITION(680.f, 440.f);
//文字列の拡大率
const DirectX::SimpleMath::Vector2 WeaponExplanatory::STRING_SCALE(0.3f, 0.3f);
//各種武器の説明文
const RECT WeaponExplanatory::STRING_RENGE = RECT{ 0,0,2025,135 };

/*===================================
コンストラクタ
引数：なし
===================================*/
WeaponExplanatory::WeaponExplanatory()
	:
	mpExplanatory(nullptr)
{
	mpExplanatory = std::make_unique<ObjectSpriteTexture>(STRING_RENGE);
}

/*===================================
デストラクタ
===================================*/
WeaponExplanatory::~WeaponExplanatory()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void WeaponExplanatory::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance(); 
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__EXPLANATORY));

	mpExplanatory->SetTexture(texture); 
	mpExplanatory->Initialize();
	mpExplanatory->SetRect(STRING_RENGE);
	mpExplanatory->SetPosition(STRING_POSITION);
	mpExplanatory->SetScale(STRING_SCALE);
}
/*===================================
更新処理
引数：描画している武器
返り値：なし
===================================*/
void WeaponExplanatory::Update(const eWeaponType& type)
{
	RECT rect = STRING_RENGE;
;
	rect.top = (static_cast<int>(type)-1)* STRING_RENGE.bottom;


	rect.bottom *= static_cast<int>(type);

	mpExplanatory->SetRect(rect);
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void WeaponExplanatory::Draw()
{
	mpExplanatory->Draw();
}
