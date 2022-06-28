/*
ワイプ
作成者：杉山
作成日：2021/12/21
*/
#include"pch.h"

#include"Wipe.h"

//前回時
const float Wipe::FULL_OPEN = 1.f;
const float Wipe::FULL_CLOSE = 0.f;

/*=================================
コンストラクタ
引数：ワイプ時間、ワイプの割合
===================================*/
Wipe::Wipe(float interval,float rate)
	:
	mInterval(interval),
	mRate (rate),
	mFlagOpen (true),
	mcbChangeEveryFrame ()
{
}

/*===================================
デストラクタ
===================================*/
Wipe::~Wipe()
{
}

/*===================================
初期化処理
引数：なし
返り値：なし
===================================*/
void Wipe::Initialize()
{
	//デバイスの取得
	const auto pDR = DX::DeviceResources::GetInstance();
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();


	//ウィンドウサイズの取得
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	//Resource生成フラグ
	HRESULT hr = E_FAIL;

	//定数バッファの作成=========================
	D3D11_BUFFER_DESC cBufferDesc{};

	cBufferDesc.ByteWidth = sizeof(cbChangeEveryFrame);
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer
	(
		&cBufferDesc,
		nullptr,
		mCbBuffer.ReleaseAndGetAddressOf()
	);
	assert(hr == S_OK && "mCbBufferの作成に失敗");


	//2Dテクスチャバッファの作成====================
	D3D11_TEXTURE2D_DESC texDesc{};

	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.Width = w;
	texDesc.Height = h;
	texDesc.ArraySize = 1;
	texDesc.MipLevels = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.CPUAccessFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;

	hr = device->CreateTexture2D
	(
		&texDesc,
		nullptr,
		mTextureBuffer.ReleaseAndGetAddressOf()
	);
	assert(hr == S_OK && "mTextureBufferの作成に失敗");

	//シェーダ―リソースビューの生成===========

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView
	(
		mTextureBuffer.Get(),
		&srvDesc,
		mShaderResourceView.ReleaseAndGetAddressOf()
	);

	//シェーダの作成=================================================

	assert(hr == S_OK && "mShaderResouceViewの作成に失敗");

	std::vector<uint8_t> blob = DX::ReadData(L"Resources/Shaders/psWipe.cso");

	hr = device->CreatePixelShader
	(
		blob.data(),
		blob.size(),
		nullptr,
		mpPixelShader.ReleaseAndGetAddressOf()
	);
	assert(hr == S_OK && "mPixelShaderの作成に失敗");

}

/*===================================
更新処理
引数：なし
返り値：なし
===================================*/
bool Wipe::Update(float elaspedTime)
{
	if (mFlagOpen)
	{
		//オープン
		mRate += elaspedTime / mInterval;
		
		mRate = std::min(mRate, FULL_OPEN);

		//終了
		if (mRate >= FULL_OPEN)
		{
			return true;
		}
	}
	else
	{
		//クローズ
		mRate -= elaspedTime / mInterval;

		mRate = std::max(mRate, FULL_CLOSE);

		//終了
		if (mRate <= FULL_CLOSE)
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
void Wipe::Draw()
{
	const auto& DxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	//全開の時は描画しない
	if (mRate >= 1.f)return;

	
	//デバイスコンテキストの取得
	const auto pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	//ウィンドウサイズの取得
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	//画面サイズの短径を設定する
	RECT rect = {0,0,w,h};

	//定数バッファの構造体の値を設定する
	mcbChangeEveryFrame.radius = mRate;
	mcbChangeEveryFrame.aspectRatio = w / static_cast<float>(h);

	//ワイプ状態を描画する
	DxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		[&]()
		{
			//定数バッファへの書き込み
			D3D11_MAPPED_SUBRESOURCE mappedResource{};
			context->Map
			(mCbBuffer.Get(),
				0,
				D3D11_MAP_WRITE_DISCARD,
				0, &mappedResource
			);

			std::memcpy
			(
				mappedResource.pData,
				&mcbChangeEveryFrame,
				sizeof(cbChangeEveryFrame)
			);
			context->Unmap(mCbBuffer.Get(), 0);

			//ピクセルシェーダに定数バッファを設定
			ID3D11Buffer* buffers[] = { mCbBuffer.Get() };
			context->PSSetConstantBuffers(0, 1, buffers);


			context->PSSetShader(mpPixelShader.Get(), nullptr, 0);
		}
	);

	DxIF.GetSpriteBatch()->Draw(mShaderResourceView.Get(), rect);
	DxIF.GetSpriteBatch()->End();

}

/*===================================
オープン状態
引数：なし
返り値：なし
===================================*/
bool Wipe::GetState()
{
	if (mFlagOpen && mRate == FULL_OPEN)
	{
		return true;
	}
	else
	{
		return false;
	}
}
