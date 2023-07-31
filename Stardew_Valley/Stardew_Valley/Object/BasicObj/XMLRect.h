#pragma once
class XMLRect
{
public:
	XMLRect(string path, string name, Vector2 size);
	~XMLRect() {}

	void Render();
	void SetRatio(Vector2 ratio);
private:
	void GetInfo(string path, string name);
	void CreateVertices();
	void CreateData();

	Vector2 _size;

	vector<VertexTexture> _vertices;
	vector<int> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;
	shared_ptr<XMLBuffer> _xBuffer;

	weak_ptr<SRV> _srv;
	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

