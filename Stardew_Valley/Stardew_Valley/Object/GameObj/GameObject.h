#pragma once
class GameObject
{
public:
	GameObject(int itemCode);
	~GameObject() {}

	void Update();
	void Render();

	void SetPos(Vector2 pos);
	void SetFrame(Vector2 frame);
	
	virtual void UseItem() abstract;
protected:
	int _itemCode;
};

