#pragma once
class Quad
{
public:
	Quad(wstring path, Vector2 maxFrame, Vector2 size);
	~Quad() {}

	virtual void Render();
	virtual void Update();

	void SetCurFrame(Vector2 frame);

protected:
	virtual void CreateVertex();
	virtual void CreateData();

	Vector2 _curFrame;
	Vector2 _size;

	vector<VertexTexture> _vertices;
	vector<int> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;
	shared_ptr<FrameBuffer> _fBuffer;


	weak_ptr<SRV> _srv;
	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};
