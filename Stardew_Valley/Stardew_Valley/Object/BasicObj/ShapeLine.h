#pragma once
#include "../../Types.h"
class ShapeLine
{
public:
	ShapeLine() {}
	~ShapeLine() {}

	void Render();
	void SetColor(XMFLOAT4 color) {_cBuffer->SetColor(color);}

protected:
	virtual void CreateVertices() abstract;
	void CreateData();

	vector<Vertex> _vertices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<ColorBuffer> _cBuffer;

	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

