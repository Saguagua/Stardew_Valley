#pragma once
class SingleColorRect
{
public:
	SingleColorRect(Vector2 size, XMFLOAT4 color = GREEN);
	~SingleColorRect() {}

	void Render();
	void SetColor(XMFLOAT4 color);
	void SetRatio(Vector2 ratio);

	void AddColor(XMFLOAT4 color);

	Vector2 GetRatio();
	XMFLOAT4 GetColor();
private:
	void CreateVertices();
	void CreateData();

	Vector2 _size;

	vector<VertexTexture> _vertices;
	vector<int> _indices;
	
	shared_ptr<ColorBuffer> _cBuffer;
	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;

	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

