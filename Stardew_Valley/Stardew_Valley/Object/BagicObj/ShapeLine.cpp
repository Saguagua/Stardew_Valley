#include "framework.h"
#include "ShapeLine.h"

void ShapeLine::Render()
{
	_cBuffer->Set_PS(0);
	_vBuffer->SetIA_VertexBuffer(0);
	_vShader.lock()->SetIA_InputLayout();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vShader.lock()->SetShader();
	_pShader.lock()->SetShader();

	DC->Draw(_vertices.size(), 0);
}

void ShapeLine::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());
	_cBuffer = make_shared<ColorBuffer>();

	_vShader = ADD_VS(L"Shader/VertexVS.hlsl");
	_pShader = ADD_PS(L"Shader/SingleColorPS.hlsl");
}
