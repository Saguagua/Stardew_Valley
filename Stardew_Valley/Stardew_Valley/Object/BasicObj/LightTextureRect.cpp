#include "framework.h"
#include "LightTextureRect.h"

LightTextureRect::LightTextureRect(wstring path, Vector2 maxFrame, Vector2 size)
	:_size(size)
{
	_transform = make_shared<Transform>();
	_srv = ADD_SRV(path);
	CreateVertices();
	CreateData();
	_fBuffer->SetMaxFrame(maxFrame);
	_fBuffer->SetStart(Vector2(0, 0));
	_fBuffer->Update();
	_lPBuffer->Update();
	_lCBuffer->Update();
}

void LightTextureRect::Render()
{
	_transform->Set_World();
	_fBuffer->Set_PS(0);
	_lPBuffer->Set_VS(3);
	_lCBuffer->Set_PS(1);
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

void LightTextureRect::SetPos(Vector2 pos)
{
	_transform->SetPos(pos);
	_transform->Update();
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

	_vShader = ADD_VS(L"Shader/LightVS.hlsl");
	_pShader = ADD_PS(L"Shader/LightPS.hlsl");

	_lPBuffer = make_shared<LightPoseBuffer>();
	_lCBuffer = make_shared<LightColorBuffer>();

	_lPBuffer->SetFirstLight(XMFLOAT4(60,60,0,0));
	_lPBuffer->SetSecondLight(XMFLOAT4(WIN_WIDTH - 60,0,0,0));
	_lPBuffer->SetThirdLight(XMFLOAT4(WIN_WIDTH - 60,WIN_HEIGHT - 60,0,0));
	_lPBuffer->SetFourthLight(XMFLOAT4(0, WIN_HEIGHT - 60,0,0));

	_lCBuffer->SetFirstLight(XMFLOAT4(10000, 0, 0, 0.0));
	_lCBuffer->SetSecondLight(XMFLOAT4(0, 10000, 0, 0.0));
	_lCBuffer->SetThirdLight(XMFLOAT4(0, 0, 10000, 0.0));
	_lCBuffer->SetFourthLight(XMFLOAT4(10000, 10000, 10000, 0));
}
