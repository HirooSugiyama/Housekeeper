/*
DirectXTKの汎用処理のシングルトン化
作成者：杉山
制作日：2021/04/23
*/
#include<pch.h>


//クラス外部で初期化
std::unique_ptr <DirectXtkComponent> DirectXtkComponent::sDirectXtkComponent = nullptr;
std::unique_ptr<DirectX::CommonStates> DirectXtkComponent::spCommonState = nullptr;
std::unique_ptr<DirectX::SpriteBatch> DirectXtkComponent::spSpriteBatch = nullptr;
std::unique_ptr<DirectX::SpriteFont> DirectXtkComponent::spSpriteFont = nullptr;

/*=========================================
コンストラクタ
引数：なし
=========================================*/
DirectXtkComponent::DirectXtkComponent()
	:
	spDevice(),
	spContext()
{
	const auto pDR = DX::DeviceResources::GetInstance();
	// D3Dデバイスとデバイスコンテキストの取得
	spDevice = pDR->GetD3DDevice();
	spContext = pDR->GetD3DDeviceContext();

	spCommonState = std::make_unique<DirectX::CommonStates>(spDevice);
	
	spSpriteBatch = std::make_unique<DirectX::SpriteBatch>(spContext);
	
	spSpriteFont = std::make_unique<DirectX::SpriteFont>(spDevice, L"Resources/Fonts/SegoeUI_18.spritefont");
}
/*=========================================
インスタンスの取得
引数：なし
返り値：自身のインスタンス
=========================================*/
DirectXtkComponent& DirectXtkComponent::GetDirectXtkComponentInstance()
{
	if (sDirectXtkComponent == nullptr)
	{
		sDirectXtkComponent.reset(new DirectXtkComponent());
	}
	return *sDirectXtkComponent;
}

/*=========================================
コモンステートのゲッター
引数：なし
返り値：コモンステート
=========================================*/
DirectX::CommonStates* DirectXtkComponent::GetCommonStates() const 
{
	return spCommonState.get();
}
/*=========================================
スプライトバッチの取得
引数：なし
返り値：スプライトバッチ
=========================================*/
DirectX::SpriteBatch* DirectXtkComponent::GetSpriteBatch() const 
{
	return spSpriteBatch.get();
}
/*=========================================
スプライトフォントの取得
引数：なし
返り値：スプライトフォント
=========================================*/
DirectX::SpriteFont* DirectXtkComponent::GetSpriteFont()const 
{
	return spSpriteFont.get();
}