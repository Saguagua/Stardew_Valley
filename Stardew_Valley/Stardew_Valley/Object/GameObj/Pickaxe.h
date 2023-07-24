#pragma once
class Pickaxe: public GameObject
{
public:
	Pickaxe(int itemCode);
	virtual ~Pickaxe() {}

	virtual void UseItem() override;

private:
	void SetProperty();

	short _damage;
	short _cost;
};

