//
// pch.h
// Header for standard system include files.
//

#pragma once


#include <winsdkver.h>
#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>

#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif

#include <DirectXMath.h>
#include <DirectXColors.h>

#include<algorithm>
#include<exception>
#include<memory>
#include<stdexcept>

#include<stdio.h>

#include<SimpleMath.h>
#include<Model.h>
#include<iostream>
#include<Mouse.h>
#include<GamePad.h>
#include<cassert>
#include<fstream>
#include<sstream>

#include<WICTextureLoader.h>
#include<string>
#include<unordered_map>
#include<random>
#include<SpriteBatch.h>
#include<SpriteFont.h>
#include<VertexTypes.h>
#include<CommonStates.h>
#include<vector>
#include <time.h>
#include"Libraries/DirectXTK/Inc/Effects.h"
#include"Libraries/MyLibraries/Animation.h"
#include <DeviceResources.h>

#include<ReadData.h>
#include <StepTimer.h>
#include <PrimitiveBatch.h>


//汎用処理
#include"Game/PlayScene/Utility.h"
#include"Game/PlayScene/Collider/Collider.h"
#include"Game/Manager/ResourceManager.h"
#include"Game/Tracker/KeyTracker.h"
#include"Game/Tracker/GamePadTracker.h"

#include"Game/Component/CameraInfoComponent/CameraInfoComponent.h"
#include"Game/Component/DirectXTKComponent/DirectXTKComponent.h"
#include"Game/Component/ScreenTransitionComponent/ScreenTransitionComponent.h"
#include"Game/Component/TimerComponent/TimerComponent.h"


#ifdef _DEBUG
#include <dxgidebug.h>
#include <crtdbg.h>     //!! 追記
#include <shtypes.h>
#endif


namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        virtual const char* what() const override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}
