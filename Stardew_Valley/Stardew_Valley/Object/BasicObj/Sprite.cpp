#include "framework.h"
#include "Sprite.h"


Sprite::Sprite(string name, Vector2 size, SpriteType type)
	:_size(size)
{
	CreateVertices();

	if (type == SpriteType::OBJECT)
		CreateObjData();
	else if (type == SpriteType::UI)
		CreateUIData();

	SetImage(name);
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

void Sprite::SetImage(string name, int index)
{
	if (_curPage != _map[name]->GetPage())
	{
		_curPage = _map[name]->GetPage();
		wstring srvPath = L"Resource/XMLResource" + _curPage + L".png";

		_srv = ADD_SRV(srvPath);
		_xBuffer->SetImgSize(_srv.lock()->GetImageSize());
	}

	_curName = name;

	XMLInfo::Position pos = _map[_curName]->GetPos(index);
	_xBuffer->SetStart(Vector2(pos.x, pos.y));
	_xBuffer->SetSize(Vector2(pos.w, pos.h));
	_xBuffer->Update();
}

void Sprite::SetIndex(int index)
{
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

void Sprite::CreateObjData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_xBuffer = make_shared<XMLBuffer>();
	_vShader = ADD_VS(L"Shader/LightVS.hlsl");
	_pShader = ADD_PS(L"Shader/LightXMLPS.hlsl");
}

void Sprite::CreateUIData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_xBuffer = make_shared<XMLBuffer>();
	_vShader = ADD_VS(L"Shader/TextureVS.hlsl");
	_pShader = ADD_PS(L"Shader/XMLPS.hlsl");
}


