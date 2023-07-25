#pragma once
class GameObject
{
public:
	GameObject(int itemCode, short count = 1);
	~GameObject() {}

	void Update();
	void Render();

	void SetPos(Vector2 pos);
	void SetFrame(Vector2 frame);
	
	virtual int UseItem() abstract;
protected:
	int _itemCode;
	int _price;
	short _count;
	short _maxCount;
};

