#include "framework.h"
#include "SingleColorRect.h"

SingleColorRect::SingleColorRect(Vector2 size, XMFLOAT4 color)
	:_size(size)
{
	CreateVertices();
	CreateData();
	_cBuffer->SetColor(color);
	_cBuffer->SetRatio(Vector2(1,1));
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

void SingleColorRect::SetRatio(Vector2 ratio)
{
	Vector2 curRatio = _cBuffer->GetRatio();
	XMFLOAT4 color = _cBuffer->GetColor();
	float del = curRatio.y - ratio.y;

	if (curRatio.y < ratio.y)
	{
		if (color.x == 1.0f)
			AddColor(XMFLOAT4(0.0f, -del * 2, 0.0f, 0.0f));
		else
			AddColor(XMFLOAT4(del * 2, 0.0f, 0.0f, 0.0f));
	}
	else if (curRatio.y > ratio.y)
	{
		if (color.y == 1.0f)
			AddColor(XMFLOAT4(-del * 2, 0.0f, 0.0f, 0.0f));
		else
			AddColor(XMFLOAT4(0.0f, -del * 2, 0.0f, 0.0f));
	}

	_cBuffer->SetRatio(ratio);
	_cBuffer->Update();
}

void SingleColorRect::AddColor(XMFLOAT4 color)
{
	_cBuffer->AddColor(color);
	_cBuffer->Update();
}

Vector2 SingleColorRect::GetRatio()
{
	return _cBuffer->GetRatio();
}

XMFLOAT4 SingleColorRect::GetColor()
{
	return _cBuffer->GetColor();
}

void SingleColorRect::CreateVertices()
{
	VertexTexture v;
	Vector2 halfSize = _size * 0.5f;

	v.pos = { -halfSize.x, halfSize.y, 0.0f}; //øﬁ¿ß
	v.uv = {0,0};
	_vertices.push_back(v);

	v.pos = { halfSize.x, halfSize.y, 0.0f }; //ø¿¿ß
	v.uv = {1,0};
	_vertices.push_back(v);

	v.pos = { halfSize.x, -halfSize.y, 0.0f }; //ø¿æ∆
	v.uv = { 1,1 };
	_vertices.push_back(v);

	v.pos = { -halfSize.x, -halfSize.y, 0.0f }; //øﬁæ∆
	v.uv = { 0,1 };
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
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_cBuffer = make_shared<ColorBuffer>();

	_vShader = ADD_VS(L"Shader/TextureVS.hlsl");
	_pShader = ADD_PS(L"Shader/RatioColorPS.hlsl");
}