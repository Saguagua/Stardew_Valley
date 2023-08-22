#pragma once
class Bar
{
public:
	Bar(wstring path, string name, Vector2 size);
	~Bar() {}

	void Render();

	void SetRatio(Vector2 ratio);
	void SetPos(Vector2 pos);

	Vector2 GetPos() { return _bodyTransform->GetPos(); }
private:
	shared_ptr<Transform> _bodyTransform;
	shared_ptr<Transform> _guageTransform;
	shared_ptr<Sprite> _body;
	shared_ptr<SingleColorRect> _gauge;
};

