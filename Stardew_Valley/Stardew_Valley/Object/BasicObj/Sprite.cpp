#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, string name, Vector2 size)
	:_curName(name), _size(size)
{
	_srv = ADD_SRV(path);
	CreateVertices();
	CreateData();
	_xBuffer->SetImgSize(_srv.lock()->GetImageSize());
	ChangePicture(_curName);
}

void Sprite::Render()
{
	LightManager::GetInstance()->Set_Shader();
	_xBuffer->Set_PS(0);

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

void Sprite::ChangePicture(string name, int index)
{
	if (name != "BLNAK")
		_curName = name;
	
	XMLInfo::Position pos = _map[_curName]->GetPos(index);
	_xBuffer->SetStart(Vector2(pos.x, pos.y));
	_xBuffer->SetSize(Vector2(pos.w, pos.h));
	_xBuffer->Update();
}

void Sprite::CreateVertices()
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

void Sprite::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_xBuffer = make_shared<XMLBuffer>();
	_vShader = ADD_VS(L"Shader/LightVS.hlsl");
	_pShader = ADD_PS(L"Shader/LightXMLPS.hlsl");
}
