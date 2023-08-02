#include "framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(wstring path, Vector2 maxFrame, Vector2 size)
	:_size(size)
{
	_srv = ADD_SRV_SIZE(path, size);

	CreateVertex();
	CreateData();

	_fBuffer->SetMaxFrame(maxFrame);
	_fBuffer->SetStart(Vector2(0,0));
	_fBuffer->Update();
}

TextureRect::TextureRect(wstring path, Vector2 maxFrame)
{
	_srv = ADD_SRV(path);
	_size = _srv.lock()->GetImageSize();
	CreateVertex();
	CreateData();

	_fBuffer->SetMaxFrame(maxFrame);
	_fBuffer->SetStart(Vector2(0, 0));
	_fBuffer->Update();
}

void TextureRect::Render()
{
	_fBuffer->Set_PS();

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

void TextureRect::SetCurFrame(int index)
{
	Vector2 maxFrame = _fBuffer->GetMaxFrame();
	Vector2 frame;
	frame.x = index % (int)maxFrame.x;
	frame.y = index / (int)maxFrame.x;
	_fBuffer->SetStart(frame);
	_fBuffer->Update();
}

void TextureRect::SetCurFrame(Vector2 frame)
{
	_fBuffer->SetStart(frame);
	_fBuffer->Update();
}

void TextureRect::CreateVertex()
{
	VertexTexture v;
	Vector2 halfSize = _size * 0.5f;

	v.pos = {-halfSize.x, halfSize.y, 0.0f};//øﬁ¿ß
	v.uv = {0, 0};
	_vertices.push_back(v);

	v.pos = { halfSize.x, halfSize.y, 0.0f };//ø¿¿ß
	v.uv = {1, 0};
	_vertices.push_back(v);
	
	v.pos = { halfSize.x, -halfSize.y, 0.0f };//ø¿æ∆
	v.uv = {1, 1};
	_vertices.push_back(v);
	
	v.pos = { -halfSize.x, -halfSize.y, 0.0f };//øﬁæ∆
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
