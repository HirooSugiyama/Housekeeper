/*
壁クラス
作成者：杉山
作成日：2021/10/21
*/

#include<pch.h>
#include"Wall.h"

/*===================================
コンストラクタ
引数：なし
===================================*/
Wall::Wall()
	:
	mpWallModel(nullptr)
{
	//モデルのメモリ確保
	mpWallModel = std::make_unique<BoxModel>();
}

/*===================================
デストラクタ
===================================*/
Wall::~Wall()
{
}
/*===================================
初期化処理
引数：position(座標)、scale(拡大率)
返り値：なし
===================================*/
void Wall::Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 scale)
{

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__FULLFENCE));
	mpWallModel->SetModel(model);
	mpWallModel->SetPosition(position);
	mpWallModel->SetScale(scale);

		/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpWallModel->ReturnHalfSize(scale);
	//設定
	mpWallModel->SetAABBCollider(position - halfsize, position + halfsize);
}

/*===================================
描画処理
引数：なし
返り値：なし
===================================*/
void Wall::Draw()
{
	mpWallModel->Draw();
}