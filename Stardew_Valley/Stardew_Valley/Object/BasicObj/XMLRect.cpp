#include "framework.h"
#include "../../Framework/Utility/tinyxml2.h"
#include "XMLRect.h"

XMLRect::XMLRect(string path, string name, Vector2 size)
	:_size(size)
{
	CreateVertices();
	CreateData();
	GetInfo(path, name);
	_xBuffer->Update();
}

void XMLRect::Render()
{
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

void XMLRect::SetRatio(Vector2 ratio)
{
	_xBuffer->SetRatio(ratio);
	_xBuffer->Update();
}

void XMLRect::GetInfo(string path, string name)
{
	string srvStringPath = path + ".png";
	wstring srvPath = wstring(srvStringPath.begin(), srvStringPath.end());
	_srv = ADD_SRV(srvPath);
	_xBuffer->SetImgSize(_srv.lock()->GetImageSize());
	
	string xmlPath = path + ".xml";
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	while (true)
	{
		if (row == nullptr)
			break;
		if (name == row->FindAttribute("n")->Value())
		{
			Vector2 startPos;
			startPos.x = row->FindAttribute("x")->IntValue();
			startPos.y = row->FindAttribute("y")->IntValue();
			Vector2 size;
			size.x = row->FindAttribute("w")->IntValue();
			size.y = row->FindAttribute("h")->IntValue();
			_xBuffer->SetStart(startPos);
			_xBuffer->SetSize(size);
			_xBuffer->Update();
			break;
		}

		row = row->NextSiblingElement();
	}
}

void XMLRect::CreateVertices()
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

void XMLRect::CreateData()
{
	_vBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexTexture), _vertices.size());
	_iBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_xBuffer = make_shared<XMLBuffer>();
	_vShader = ADD_VS(L"Shader/TextureVS.hlsl");
	_pShader = ADD_PS(L"Shader/XMLPS.hlsl");
}
