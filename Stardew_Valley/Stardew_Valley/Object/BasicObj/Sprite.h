#pragma once
class Sprite
{
public:
	Sprite(wstring path, string name, Vector2 size);
	~Sprite() {}

	string GetName() { return _curName; }
	void SetName(string name) { _curName = name; }

	void Render();
	void ChangePicture(int index, string name = "");

private:
	void CreateVertices();
	void CreateData();

	string _curName;
	Vector2 _size;

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

