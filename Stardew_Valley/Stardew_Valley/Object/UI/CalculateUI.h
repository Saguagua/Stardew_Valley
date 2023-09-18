#pragma once
class CalculateUI
{
public:
	CalculateUI(wstring typeName, Vector2 size);
	~CalculateUI() {}

	void Render();
	void PostRender();

	void Update();

	void SetPrice(short cost);

	void SetPos(Vector2 pos);
private:
	shared_ptr<Transform> _bodySlot;

	Vector2 _fontWorld;
	Vector2 _typePos;
	Vector2 _pricePos;
	Vector2 _goldPos;

	shared_ptr<Sprite> _body;

	wstring _typeName;
	wstring _price = L"0";
};

