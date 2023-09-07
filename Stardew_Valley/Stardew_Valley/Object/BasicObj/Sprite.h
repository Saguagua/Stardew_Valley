#pragma once
class DataManager;

class Sprite
{
public:
	Sprite(string name, Vector2 size, SpriteType type);
	Sprite(wstring path, string name, Vector2 size, SpriteType type);
	~Sprite() {}

	void Render();
	
	void SetImage(string name, int index = 0);
	
	string GetName() { return _curName; }
	int GetIndex() { return _index; }

private:
	void CreateVertices();
	void CreateObjData();
	void CreateUIData();

	string _curName;
	Vector2 _size;

	wstring _curPage = L"0";
	int _index;

	vector<VertexTexture> _vertices;
	vector<int> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;
	shared_ptr<XMLBuffer> _xBuffer;

	weak_ptr<SRV> _srv;
	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;

	unordered_map<string, shared_ptr<XMLInfo>>& _map = DATA->GetXMLInfos();;
};

