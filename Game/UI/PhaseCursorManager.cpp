/*
フェーズが始まるタイミングを示すカーソルの描画を行うクラス
作成者：杉山
作成日：2021/10/21
*/
#include"pch.h"

#include"PhaseCursorManager.h"


//取得座標のずらす量
const float PhaseCursorManager::PHASECURSOR_SHIFT_POSITION = 30.f;


/*===================================
コンストラクタ
引数：なし
===================================*/
PhaseCursorManager::PhaseCursorManager()
	:
	mpPhaseCursor()
{
}

/*===================================
デストラクタ
===================================*/
PhaseCursorManager::~PhaseCursorManager()
{
}

/*===================================
初期化処理
引数：最大フェーズ数
返り値：なし
===================================*/
void PhaseCursorManager::Initialize(const int& phasemaxnum)
{
	mpPhaseCursor.resize(phasemaxnum);

	//例外的にここで動的確保を行う
	for (int i = 0; i < phasemaxnum; i++)
	{
		mpPhaseCursor[i] = std::make_unique<PhaseCursor>();
	}

	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->Initialize();
	}
}


/*=================================
描画処理
引数：なし
返り値：なし
===================================*/
void PhaseCursorManager::Draw()
{
	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->Draw();
	}
}

/*===================================
描画する座標を決める
引数：描画開始座標、ずらす幅
返り値：なし
===================================*/
void PhaseCursorManager::SetDrawPosition(const DirectX::SimpleMath::Vector2& startpos, 
									const float& movepos)
{
	//一つ一つの間隔を算出
	float intervel = movepos / static_cast<int>(mpPhaseCursor.size());
	DirectX::SimpleMath::Vector2 position =
		startpos+ DirectX::SimpleMath::Vector2(PHASECURSOR_SHIFT_POSITION,0.f);

	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->SetPosition(position);
		position.x += intervel;
	}
}
