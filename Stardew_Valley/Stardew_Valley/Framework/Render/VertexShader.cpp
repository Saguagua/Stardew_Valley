#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring path)
	:Shader(path)
{
	CreateBlob(path);
	CreateInputLayout(path);
	CreateShader();
}

void VertexShader::CreateBlob(wstring path)
	
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(path.c_str(),
		nullptr, nullptr, "VS", "vs_5_0", flags, 0, _blob.GetAddressOf(), nullptr);
}

void VertexShader::CreateShader()
{
	DEVICE->CreateVertexShader(_blob->GetBufferPointer(),
		_blob->GetBufferSize(), nullptr, IN _vs.GetAddressOf());
}

void VertexShader::CreateInputLayout(wstring path)
{
    if (path == L"Shader/VertexVS.hlsl")
    {
        D3D11_INPUT_ELEMENT_DESC layOut[] =
        {
            {
                "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,
                D3D11_INPUT_PER_VERTEX_DATA,0
            }
        };

        UINT layOutSize = ARRAYSIZE(layOut);

        DEVICE->CreateInputLayout(layOut, layOutSize,
            _blob->GetBufferPointer(), _blob->GetBufferSize(), IN _inputLayout.GetAddressOf());
    }
    else if (path == L"Shader/TextureVS.hlsl" 
        || path == L"Shader/SingleColorVS.hlsl"
        || path == L"Shader/LightVS.hlsl")
    {
        D3D11_INPUT_ELEMENT_DESC layOut[] =
        {
            {
                "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,
                D3D11_INPUT_PER_VERTEX_DATA,0
            },
            {
                "UV",0, DXGI_FORMAT_R32G32_FLOAT,0,12,
                D3D11_INPUT_PER_VERTEX_DATA,0
            }
        };

        UINT layOutSize = ARRAYSIZE(layOut);

        DEVICE->CreateInputLayout(layOut, layOutSize,
            _blob->GetBufferPointer(), _blob->GetBufferSize(), IN _inputLayout.GetAddressOf());
    }
}


void VertexShader::SetIA_InputLayout()
{
    DC->IASetInputLayout(_inputLayout.Get());
}

void VertexShader::SetShader()
{
    DC->VSSetShader(_vs.Get(), nullptr, 0);
}
