//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

// 静的データメンバの定義
const wchar_t* Game::TITLE = L"Housekeeper";
const int Game::SCREEN_W = 1280;
const int Game::SCREEN_H = 780;

extern void ExitGame();



using Microsoft::WRL::ComPtr;



Game::Game() noexcept(false)
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    pDR->RegisterDeviceNotify(this);

}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    pDR->SetWindow(window, width, height);

    pDR->CreateDeviceResources();
    CreateDeviceDependentResources();

    pDR->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */


    // シーンの作成
    mGameMain = std::make_unique<GameMain>();
    mGameMain->Initialize();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(const DX::StepTimer& timer)
{

    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

    // 追加した
    mGameMain->Update(timer);
   

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    pDR->PIXBeginEvent(L"Render");
    auto context = pDR->GetD3DDeviceContext();

    // TODO: Add your rendering code here.

    context;

    pDR->PIXEndEvent();

    // 追加した
    mGameMain->Render();

    // Show the new frame.
    pDR->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
  
    pDR->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = pDR->GetD3DDeviceContext();
    auto renderTarget = pDR->GetRenderTargetView();
    auto depthStencil = pDR->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, DirectX::Colors::MidnightBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = pDR->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    pDR->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    auto r = pDR->GetOutputSize();
    pDR->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    if (!pDR->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width  = Game::SCREEN_W;    //width = 800;
    height = Game::SCREEN_H;    //height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
    
    auto device = pDR->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}
//ウィンドウサイズの固定
void Game::SetWindowSize(HWND window)
{
    LPRECT window_rect=0, client_rect = 0;

    // ウィンドウ全体のサイズを取得
    GetWindowRect(window, window_rect);
    // クライアント領域のサイズを取得
    GetClientRect(window, client_rect);


    // フレームサイズ算出
    //int frame_size_x = (window_rect->right - window_rect->left) - (client_rect->right - client_rect->left);
    //int frame_size_y = (window_rect->bottom - window_rect->top) - (client_rect->bottom - client_rect->top);
    // リサイズ用サイズの算出
    // int resize_width = frame_size_x + width;
    // int resize_height = frame_size_y + height;

}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
