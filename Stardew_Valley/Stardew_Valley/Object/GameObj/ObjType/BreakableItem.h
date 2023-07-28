#pragma once
class BreakableItem : public GameObject
{
public:
	BreakableItem(int objCode, int frameIndex, short hp, short itemCodeMin, short itemCodeMax, short min, short max)
		:GameObject(objCode, frameIndex, 1, 1), _hp(hp), _dropItemCodeMin(itemCodeMin), _dropItemCodeMax(itemCodeMax),
		_countMin(min), _countMax(max)
	{
		_type = ObjectInfo::Type::BREAKABLE;
	}
	virtual ~BreakableItem() {}

	virtual void Interaction() override;

	void SetPos(Vector2 pos) { _pos = pos; }
	void GetDamage(shared_ptr<class PickAxe> obj);
private:
	Vector2 _pos;
	short _hp;
	short _dropItemCodeMin;
	short _dropItemCodeMax;
	short _countMin;
	short _countMax;
};

