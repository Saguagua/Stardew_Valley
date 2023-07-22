#include "framework.h"
#include "SingleColorRect.h"

SingleColorRect::SingleColorRect(Vector2 size, XMFLOAT4 color)
	:_size(size)
{
	CreateVertices();
	CreateData();
	_cBuffer->SetColor(color);
	_cBuffer->Update();
}

void SingleColorRect::Render()
{
	_cBuffer->Set_PS(0);
	_vBuffer->SetIA_VertexBuffer();
	_iBuffer->SetIA_IndexBuffer();
	_vShader.lock()->SetIA_InputLayout();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_vShader.lock()->SetShader();
	_pShader.lock()->SetShader();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void SingleColorRect::SetColor(XMFLOAT4 color)
{
	_cBuffer->SetColor(color);
	_cBuffer->Update();
}

void SingleColorRect::CreateVertices()
{
	Vertex v;

	v.pos = {0.0f, _size.y, 0.0f};
	_vertices.push_back(v);

	v.pos = { _size.x, _size.y, 0.0f };
	_vertices.push_back(v);

	v.pos = { _size.x, 0.0f, 0.0f };
	_vertices.push_back(v);

	v.pos = { 0.0f, 0.0f, 0.0f };
	_vertices.push_back(v);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_indices.push_back(0);
	_indices.push_back(2);
	_indices.push_back(3);
}

void SingleColorRect::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_cBuffer = make_shared<ColorBuffer>();

	_vShader = ADD_VS(L"Shader/VertexVS.hlsl");
	_pShader = ADD_PS(L"Shader/SingleColorPS.hlsl");
}
