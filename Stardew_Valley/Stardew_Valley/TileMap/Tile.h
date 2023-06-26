#pragma once
class Tile
{

public:
	Tile(Vector2 size);
	~Tile() {}

	void Update();
	void Render();

private:
	void CreateVertices();
	void CreateData();

	vector<Vertex> _vertices;
	vector<int> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<ColorBuffer> _cBuffer;

	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;

	Vector2 _size = {1, 1};
	XMFLOAT4 _color = GREEN;
};

