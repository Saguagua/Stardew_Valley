#include "framework.h"
#include "RectLine.h"

RectLine::RectLine(Vector2 size)
	:_size(size)
{
	CreateVertices();
	CreateData();
	
	_cBuffer->SetColor(_color);
	_cBuffer->Update();
}

void RectLine::Render()
{
	_cBuffer->Set_PS(0);
	_vBuffer->SetIA_VertexBuffer(0);
	_vShader.lock()->SetIA_InputLayout();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vShader.lock()->SetShader();
	_pShader.lock()->SetShader();

	DC->Draw(_vertices.size(), 0);
}

void RectLine::CreateVertices()
{
	Vertex v = {};

	Vector2 halfSize = _size * 0.5f;

	v.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
	_vertices.push_back(v);

	v.pos = { halfSize.x, halfSize.y, 0.0f }; // 오른쪽 위
	_vertices.push_back(v);

	v.pos = { halfSize.x, -halfSize.y, 0.0f }; // 오른쪽 아래
	_vertices.push_back(v);

	v.pos = { -halfSize.x, -halfSize.y, 0.0f }; // 왼쪽 아래
	_vertices.push_back(v);

	v.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
	_vertices.push_back(v);
}

void RectLine::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());
	_cBuffer = make_shared<ColorBuffer>();

	_vShader = ADD_VS(L"Shader/VertexVS.hlsl");
	_pShader = ADD_PS(L"Shader/SingleColorPS.hlsl");
}