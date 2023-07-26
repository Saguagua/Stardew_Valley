#pragma once
class BreakableItem : public GameObject
{
public:
	BreakableItem(int itemCode, short count, short hp);
	~BreakableItem() {}

	virtual void Interaction() override;

	void SetPos(Vector2 pos) { _pos = pos; }
	void GetDamage(int amount);
private:
	Vector2 _pos;
	short _hp;
	int _dropItemCode;
	int _dropItemCount;
};

