#include "framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(wstring path, Vector2 maxFrame, Vector2 size)
	:_size(size)
{
	_srv = ADD_SRV(path);

	CreateVertex();
	CreateData();

	_fBuffer->SetMaxFrame(maxFrame);
}

void TextureRect::Render()
{
	_fBuffer->Set_PS(1);

	_vBuffer->SetIA_VertexBuffer();
	_iBuffer->SetIA_IndexBuffer();
	_vShader.lock()->SetIA_InputLayout();
	
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_srv.lock()->SetSRV(0);
	SAMPLER->SetSampler();

	_vShader.lock()->SetShader();
	_pShader.lock()->SetShader();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void TextureRect::Update()
{
	_fBuffer->SetStart(_curFrame);
	_fBuffer->Update();
}

void TextureRect::SetCurFrame(Vector2 frame)
{
	Vector2 max = _fBuffer->GetMaxFrame();
	if (frame.x > -1 && frame.x < max.x
		&& frame.y > -1 && frame.y < max.y)
		_curFrame = frame;
}

void TextureRect::CreateVertex()
{
	VertexTexture v;
	Vector2 halfSize = _size * 0.5f;

	v.pos = {-halfSize.x, halfSize.y, 0.0f};//¿ÞÀ§
	v.uv = {0, 0};
	_vertices.push_back(v);

	v.pos = { halfSize.x, halfSize.y, 0.0f };//¿ÀÀ§
	v.uv = {1, 0};
	_vertices.push_back(v);
	
	v.pos = { halfSize.x, -halfSize.y, 0.0f };//¿À¾Æ
	v.uv = {1, 1};
	_vertices.push_back(v);
	
	v.pos = { -halfSize.x, -halfSize.y, 0.0f };//¿Þ¾Æ
	v.uv = {0, 1};
	_vertices.push_back(v);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_indices.push_back(0);
	_indices.push_back(2);
	_indices.push_back(3);
}

void TextureRect::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_fBuffer = make_shared<FrameBuffer>();

	_vShader = ADD_VS(L"Shader/TextureVS.hlsl");
	_pShader = ADD_PS(L"Shader/ClipFilterPS.hlsl");
}
