#pragma once
class ShapeLine
{
public:
	ShapeLine() {}
	virtual ~ShapeLine() {}

	void Render();
	void SetColor(XMFLOAT4 color) { _cBuffer->SetColor(color); _cBuffer->Update(); }

protected:
	virtual void CreateVertices() abstract;
	void CreateData();

	vector<Vertex> _vertices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<ColorBuffer> _cBuffer;

	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

