#pragma once
class SingleColorRect
{
public:
	SingleColorRect(Vector2 size, XMFLOAT4 color = GREEN);
	~SingleColorRect() {}

	void Render();
	void SetColor(XMFLOAT4 color);

private:
	void CreateVertices();
	void CreateData();

	Vector2 _size;

	vector<Vertex> _vertices;
	vector<int> _indices;
	
	shared_ptr<ColorBuffer> _cBuffer;
	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;

	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

