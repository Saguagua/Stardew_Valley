#pragma once
class Transform
{
public:
	Transform();
	~Transform() {}

	void Update();
	void Update_VS();
	void Update_SRT();

	void Set_World(UINT slot = 0);
	void SetParent(shared_ptr<Transform> other) { _parent = other; }

	void SetPos(Vector2 pos) { _pos = pos; Update_SRT(); }
	void SetScale(Vector2 scale) { _scale = scale; }
	void SetAngle(float angle) { _angle = angle; }

	void AddPos(Vector2 pos) { _pos += pos; }
	void AddScale(Vector2 scale) { _scale += scale; }
	void AddAngle(float angle) { _angle += angle; }

	Vector2 GetPos() { return _pos; }
	Vector2 GetScale() { return _scale; }
	Vector2 GetWorldPos();
	Vector2 GetWorldScale();

	XMMATRIX GetSRT() { return _srt; }

private:
	shared_ptr<class MatrixBuffer> _buffer;

	Vector2 _scale = {1,1};
	Vector2 _pos = { 0,0 };
	float _angle = 0.0f;
	
	XMMATRIX _srt = XMMatrixIdentity();
	XMMATRIX _posM = XMMatrixIdentity();

	weak_ptr<Transform> _parent;
};

