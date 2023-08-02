#pragma once
class LightTextureRect
{
public:
	LightTextureRect(wstring path, Vector2 maxFrame, Vector2 size);
	~LightTextureRect() {}

	void Render();

	void SetPos(Vector2 pos); 
	void SetCurFrame(Vector2 frame);
	void SetCurFrame(int index);

	Vector2 GetMaxFrame() { return _fBuffer->GetMaxFrame(); }
	Vector2 GetCurFrame() { return _fBuffer->GetStart(); }

private:
	void CreateVertices();
	void CreateData();

	Vector2 _size;

	shared_ptr<Transform> _transform;

	vector<VertexTexture> _vertices;
	vector<int> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _iBuffer;
	shared_ptr<FrameBuffer> _fBuffer;
	shared_ptr<LightPoseBuffer> _lPBuffer;
	shared_ptr<LightColorBuffer> _lCBuffer;

	weak_ptr<SRV> _srv;
	weak_ptr<VertexShader> _vShader;
	weak_ptr<PixelShader> _pShader;
};

