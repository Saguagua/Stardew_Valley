#pragma once
class DataManager;

class Sprite
{
public:
	Sprite(wstring path, string name, Vector2 size);
	~Sprite() {}

	void Render();
	void ChangePicture(int index, string name = "BLANK");
	
	string GetName() { return _curName; }
	int GetIndex() { return _index; }

	void SetName(string name);
	void SetIndex(int index);

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

