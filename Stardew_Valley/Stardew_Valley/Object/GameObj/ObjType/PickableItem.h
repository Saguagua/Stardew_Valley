#pragma once
class PickableItem :public GameObject
{
public:
	PickableItem(int objCode):GameObject(objCode) {}
	virtual ~PickableItem() {}
	virtual void Interaction() override;
};

