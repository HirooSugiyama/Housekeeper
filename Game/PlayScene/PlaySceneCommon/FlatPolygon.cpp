/*
指定された物体の影を表示するクラス
作成者：杉山
作成日：2021/09/23
*/
#include "pch.h"
#include "FlatPolygon.h"

/*=============================
コンストラクタ
引数：なし
===============================*/
FlatPolygon::FlatPolygon()
	:
	FlatPolygonBase(),
	mScale(),
	mTexture(nullptr),
	mInputLayout(nullptr)
{
}

/*=========================
デストラクタ
=========================*/
FlatPolygon::~FlatPolygon()
{

}

/*==================================
初期化
引数：なし
返り値：なし
===================================*/
void FlatPolygon::Initialize()
{
	const auto pDR = DX::DeviceResources::GetInstance();
	ResourceManager* pRM = ResourceManager::GetInstance();

	// テクスチャの読み込み
	mTexture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SHADOW));


	// プリミティブバッチの作成 
	mpPrimitiveBatch =
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(pDR->GetD3DDeviceContext());


	//ベーシックエフェクトの作成
	mpBasicEffect = std::make_unique<DirectX::BasicEffect>(pDR->GetD3DDevice());

	//入力レイアウトを作成するために必要な情報
	const void* shaderByteCode;
	size_t byteCodeLength;

	//頂点情報を決定するために必要な情報
	mpBasicEffect->SetLightingEnabled(false);		//ライトOFF
	mpBasicEffect->SetTextureEnabled(true);			//テクスチャON
	mpBasicEffect->SetVertexColorEnabled(false);	//頂点カラーOFF

	//使用する頂点シェーダー情報の取得
	mpBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//入力レイアウトの作成
	pDR->GetD3DDevice()->CreateInputLayout(
		DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		mInputLayout.GetAddressOf()
	);

	//プリミティブバッチの作成
	mpPrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>
		(pDR->GetD3DDeviceContext());
}



/*=========================
描画処理
引数：描画座標
返り値：なし
=========================*/
void FlatPolygon::Draw(const DirectX::SimpleMath::Vector3& position)
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	const auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();
	const auto pDR = DX::DeviceResources::GetInstance();

	// D3Dデバイスとデバイスコンテキストの取得
	auto* context = pDR->GetD3DDeviceContext();


	//実座標の指定用変数の宣言
	float polyRight, polyLeft, polyTop, polyBottom;

	polyRight = position.x + mScale.x;
	polyLeft = position.x - mScale.x;
	polyTop = position.z + mScale.y;
	polyBottom = position.z - mScale.y;

	//エフェクトに各種変換行列の指定（ワールド行列以外）
	mpBasicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	mpBasicEffect->SetView(*pCiIF.GetView());				//ビュー行列の設定
	mpBasicEffect->SetProjection(*pCiIF.GetProjection());	//射影行列の設定
	mpBasicEffect->SetTexture(mTexture.Get());
	mpBasicEffect->Apply(context);
	//入力アセンブラステージに入力レイアウトを設定
	context->IASetInputLayout(mInputLayout.Get());
	//半透明合成の設定:NonPremultiplied->画像がストレート・αチャンネルの場合
	context->OMSetBlendState(pDxIF.GetCommonStates()->NonPremultiplied(), nullptr,
		0xFFFFFFFF);


	//ピクセルシェーダにサンプラ（テクスチャの扱い方）を指定する
	auto sampler = pDxIF.GetCommonStates()->LinearWrap();
	context->PSSetSamplers(0, 1, &sampler);

	//ラスタライザステートの設定：背面化リング(陰面消去)しない->ポリゴンの裏面も表示
	context->RSSetState(pDxIF.GetCommonStates()->CullNone());

	//// 頂点情報（板ポリゴンの頂点） 
	DirectX::VertexPositionTexture vertex[4] =
	{
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, position.y, polyTop),
			DirectX::SimpleMath::Vector2(0.f, 0.f)
		),	//左上	
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight, position.y, polyTop),
			DirectX::SimpleMath::Vector2(0.f, 1.f)
		),	//右上
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, position.y, polyBottom),
			DirectX::SimpleMath::Vector2(1.f,0.f)
		),	//左下
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight,position.y, polyBottom),
			DirectX::SimpleMath::Vector2(1.f, 1.f)
		),//右下
	};

	static const uint16_t indices[] = {
		0,1,2,		//1枚目の三角形
		1,3,2		//2枚目の三角形
	};
	//プリミティブバッチの作成
	mpPrimitiveBatch->Begin();

	//頂点インデックスを使った描画
	mpPrimitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indices,
		(sizeof(indices) / sizeof(indices[0])),
		vertex,
		(sizeof(vertex) / sizeof(vertex[0]))
	);

	//プリミティブバッチの終了
	mpPrimitiveBatch->End();
}

/*=======================
描画処理
引数：画像の鍵
返り値：なし
=========================*/
void FlatPolygon::SetTexture(const int& texPath)
{
	ResourceManager* pRM = ResourceManager::GetInstance();

	// テクスチャの読み込み
	mTexture = pRM->GetTexture(texPath);

}

