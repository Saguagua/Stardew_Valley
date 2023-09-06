#pragma once
class LightTextureRect
{
public:
	LightTextureRect(wstring path, Vector2 maxFrame, Vector2 size);
	~LightTextureRect() {}

	void Render();

	void SetCurFrame(Vector2 frame);
	void SetCurFrame(int index);

	Vector2 GetMaxFrame() { return _fBuffer->GetMaxFrame(); }
	Vector2 GetCurFrame() { return _fBuffer->GetStart(); }

	shared_ptr<EffectBuffer> GetEBuffer() { return _eBuffer; }
private:
	void CreateVertices();
	void CreateData();

	Vector2 _size;

	vector<VertexTexture> _vertices;
	vector<int> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;
	shared_ptr<FrameBuffer> _fBuffer;
	shared_ptr<EffectBuffer> _eBuffer;

	weak_ptr<SRV> _srv;
	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

