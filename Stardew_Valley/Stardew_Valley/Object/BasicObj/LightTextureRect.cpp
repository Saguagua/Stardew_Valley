#include "framework.h"
#include "LightTextureRect.h"

LightTextureRect::LightTextureRect(wstring path, Vector2 maxFrame, Vector2 size)
	:_size(size)
{
	_srv = ADD_SRV(path);
	CreateVertices();
	CreateData();
	_fBuffer->SetMaxFrame(maxFrame);
	_fBuffer->SetStart(Vector2(0, 0));
	_fBuffer->Update();
	_eBuffer->Update();
}

void LightTextureRect::Render()
{
	_vBuffer->SetIA_VertexBuffer();
	_iBuffer->SetIA_IndexBuffer();

	_fBuffer->Set_PS();
	LightManager::GetInstance()->Set_Shader();
	_eBuffer->Set_PS(2);

	_vShader.lock()->SetIA_InputLayout();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_srv.lock()->SetSRV(0);
	SAMPLER->SetSampler();

	_vShader.lock()->SetShader();
	_pShader.lock()->SetShader();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void LightTextureRect::SetCurFrame(Vector2 frame)
{
	_fBuffer->SetStart(frame);
	_fBuffer->Update();
}

void LightTextureRect::SetCurFrame(int index)
{
	int frameLen = _fBuffer->GetMaxFrame().x;
	Vector2 newFrame;
	newFrame.x = index % frameLen;
	newFrame.y = index / frameLen;
	_fBuffer->SetStart(newFrame);
	_fBuffer->Update();
}

void LightTextureRect::CreateVertices()
{
	VertexTexture v;
	Vector2 halfSize = _size * 0.5f;

	v.pos = { -halfSize.x, halfSize.y, 0.0f };//øﬁ¿ß
	v.uv = { 0, 0 };
	_vertices.push_back(v);

	v.pos = { halfSize.x, halfSize.y, 0.0f };//ø¿¿ß
	v.uv = { 1, 0 };
	_vertices.push_back(v);

	v.pos = { halfSize.x, -halfSize.y, 0.0f };//ø¿æ∆
	v.uv = { 1, 1 };
	_vertices.push_back(v);

	v.pos = { -halfSize.x, -halfSize.y, 0.0f };//øﬁæ∆
	v.uv = { 0, 1 };
	_vertices.push_back(v);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_indices.push_back(0);
	_indices.push_back(2);
	_indices.push_back(3);
}

void LightTextureRect::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_fBuffer = make_shared<FrameBuffer>();
	_eBuffer = make_shared<EffectBuffer>();

	_vShader = ADD_VS(L"Shader/LightVS.hlsl");
	_pShader = ADD_PS(L"Shader/LightPS.hlsl");
}
