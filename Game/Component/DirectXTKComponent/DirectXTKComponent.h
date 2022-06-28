/*
DirectXTKの汎用処理のシングルトン
作成者：杉山
制作日：2021/04/23
*/
#pragma once


namespace DirectX 
{
	class CommonStates;
	class SpriteFont;
	class SpriteBatch;
}

class DirectXtkComponent final
{
private:
	//自身
	static std::unique_ptr <DirectXtkComponent> sDirectXtkComponent;
	
	//コモンステート
	static std::unique_ptr<DirectX::CommonStates> spCommonState;
	// スプライトバッチ
	static std::unique_ptr<DirectX::SpriteBatch> spSpriteBatch;
	// スプライトフォント
	static std::unique_ptr<DirectX::SpriteFont> spSpriteFont;



	//D3Dデバイスとデバイスコンテキスト
	ID3D11Device1* spDevice;
	ID3D11DeviceContext1* spContext;

	//コピーコンストラクタ、コピー代入演算子をdelete
	DirectXtkComponent(const DirectXtkComponent& dxtk) = delete;
	DirectXtkComponent operator=(const DirectXtkComponent& dxtk) = delete;

	//コンストラクタ
	DirectXtkComponent();
public:

	//自身のインスタンス
	static DirectXtkComponent& GetDirectXtkComponentInstance();

	//各ポインタのゲッター
	DirectX::CommonStates* GetCommonStates()const;
	DirectX::SpriteBatch* GetSpriteBatch()const;
	DirectX::SpriteFont* GetSpriteFont()const;

};