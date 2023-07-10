#include "framework.h"
#include "Device.h"

Device* Device::_instance = nullptr;

Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateRenderTarget();
}

void Device::Clear()
{
    FLOAT myColorR = 0.3f;
    FLOAT myColorG = 0.3f;
    FLOAT myColorB = 0.3f;

    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    _deviceContext->ClearRenderTargetView(_renderTarget.Get(), clearColor);
}

void Device::Present()
{
    _swapChain->Present(0, 0);
}

void Device::CreateDeviceAndSwapChain()
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    clientSize.x = rc.right - rc.left;
    clientSize.y = rc.bottom - rc.top;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = clientSize.x;
    sd.BufferDesc.Height = clientSize.y;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        IN _swapChain.GetAddressOf(),
        IN _device.GetAddressOf(),
        nullptr,
        IN _deviceContext.GetAddressOf()
    );
}

void Device::CreateRenderTarget()
{
    ComPtr<ID3D11Texture2D> backBuffer;

    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTarget.GetAddressOf());

    _deviceContext->OMSetRenderTargets(1, _renderTarget.GetAddressOf(), nullptr);
}