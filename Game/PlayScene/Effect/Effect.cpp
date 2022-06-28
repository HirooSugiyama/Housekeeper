/*
3D座標に2D画像を描画する汎用クラス
(使用例：エフェクトなど)
作成者：杉山
作成日：2021/09/02
*/
#include "pch.h"
#include "Effect.h"

const float EffectSpriteTexture::UV_POSITION_MAX = 1.f;

/*=========================================================================
コンストラクタ
引数：linenum(縦列最大数)、position(描画座標)、scale(拡大率)
=========================================================================*/
EffectSpriteTexture::EffectSpriteTexture(const int& linenum,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector2& scale)
	:
	mPosition(position),
	mScale(scale),
	mpSpriteBatch(),
	mSpriteTimer(),
	mConstTimer(0),
	mSpriteFlag(false),
	mLineMaxNum(linenum),
	mLineNum(0),
	mHorizontalCutNum(0),
	mWidthNum(0),
	mWidthIncreaseNum(0.f),
	mHeightIncreaseNum(0.f),
	mSpriteSrc(),
	mTexture(nullptr),
	mInputLayout(nullptr),
	mpPrimitiveBatch(nullptr),
	mpBasicEffect(nullptr),

	mWorld(),
	mCamera(),
	mLoopFlag(true),
	mAlpha(1.f)
{
}

/*=========================
デストラクタ
=========================*/
EffectSpriteTexture::~EffectSpriteTexture()
{

}

/*=========================
画像の指定
引数：画像パス
返り値：なし
=========================*/
void EffectSpriteTexture::SetFileName(const wchar_t* filepath)
{
	const auto pDR = DX::DeviceResources::GetInstance();


	// D3Dデバイスとデバイスコンテキストの取得
	auto device = pDR->GetD3DDevice();



	// テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(device, filepath, nullptr,
		mTexture.ReleaseAndGetAddressOf());
}

/*=========================
画像の指定
引数：画像情報
返り値：なし
=========================*/
void EffectSpriteTexture::SetTexture(ID3D11ShaderResourceView* texture)
{
	mTexture = texture;
}

/*=====================================
初期化
引数：描画に必要なバッチのポインタ
返り値：なし
===================================*/
void EffectSpriteTexture::Initialize()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	const auto pDR = DX::DeviceResources::GetInstance();

	//ポインタの保存
	mpSpriteBatch = pDxIF.GetSpriteBatch();

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

	//１/分割数で増加量が求められる
	mWidthIncreaseNum = UV_POSITION_MAX / static_cast<float>(mHorizontalCutNum);
	mHeightIncreaseNum = UV_POSITION_MAX / static_cast<float>(mLineMaxNum);
}



/*=========================
更新処理
引数：なし
返り値：なし
=========================*/
void EffectSpriteTexture::Update()
{
	if (mSpriteFlag)
	{
		//スプライトタイマーを回す
		mSpriteTimer++;
		//もしスプライトを回すタイミングが来たら
		if (mConstTimer == mSpriteTimer)
		{
			//タイマーは初期化する
			mSpriteTimer = 0;

			//横にスプライトを一つずらす
			mWidthNum++;

		}
		//もし画像右端により右に行ったら
		if (mWidthNum > mHorizontalCutNum)
		{
			//行数を一つずらす
			mLineNum++;

			//もし画面右端の最終行に行ったら
			if (mLineMaxNum <= mLineNum)
			{
				
				//横列のスプライトを最初の位置に戻す
				mWidthNum = 0;
				//行数などすべてリセット
				mLineNum = 0;			
				//もしループがオフなら
				if (mLoopFlag == false)
				{
					//スプライトを終了する
					mSpriteFlag = false;

					return;
				}
			}
			//それ以外(画像右端だけど、最終行じゃない場合)
			else
			{
				//横列のスプライトを最初の位置に戻す
				mWidthNum = 0;
			}
			//タイマー初期化
			mSpriteTimer = 0;
		}
	}
}
/*=======================
描画処理
引数：なし
返り値：なし
=========================*/
void EffectSpriteTexture::ExtendDraw()
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	const auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();
	const auto pDR = DX::DeviceResources::GetInstance();

	//デバイスコンテキストの取得
	auto* context = pDR->GetD3DDeviceContext();


	DirectX::SimpleMath::Matrix reverseView = pCiIF.GetView()->Invert();

	//移動行列を無効化
	reverseView._41 = 0.f;
	reverseView._42 = 0.f;
	reverseView._43 = 0.f;

	DirectX::SimpleMath::Vector3 position = mPosition;

	mWorld = reverseView * DirectX::SimpleMath::Matrix::CreateTranslation(position);



	position.x = mWorld._31;
	position.y = mWorld._32;
	position.z = mWorld._33;



	//切り取り座標の指定用変数の宣言
	float right, left, top, bottom;

	left = mWidthIncreaseNum * mWidthNum;
	right = mWidthIncreaseNum * (mWidthNum + 1);


	top = mHeightIncreaseNum * mLineNum;
	bottom = mHeightIncreaseNum * (mLineNum + 1);

	//実座標の指定用変数の宣言
	float polyRight(0.f), polyLeft(0.f), polyTop(0.f), polyBottom(0.f);


	polyRight = position.x + mScale.x;
	polyLeft = position.x - mScale.x;
	polyTop = position.y + mScale.y;
	polyBottom = position.y - mScale.y;

	//エフェクトに各種変換行列の指定（ワールド行列以外）
	mpBasicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	mpBasicEffect->SetWorld(mWorld);
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

	//// 頂点情報（板ポリゴンの頂点） 
	DirectX::VertexPositionTexture vertex[4] =
	{
		//左上
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, polyTop, position.z),
			DirectX::SimpleMath::Vector2(left, top)
		),

		//右上
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight, polyTop, position.z),
			DirectX::SimpleMath::Vector2(right, top)
		),

		//左下
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, polyBottom, position.z),
			DirectX::SimpleMath::Vector2(left,bottom)
		),

		//右下
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight,polyBottom, position.z),
			DirectX::SimpleMath::Vector2(right, bottom)
		)
	};

	static const uint16_t indices[] = 
	{
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


/*=========================
終了処理
引数：なし
返り値：なし
=========================*/
void EffectSpriteTexture::Finalize()
{
}
