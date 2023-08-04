#pragma once
class ItemSlot : public List
{
public:
	ItemSlot();
	virtual ~ItemSlot() {}

	void Update();

	void PushButtonEvent(int index);
private:
	void CreateButtons(wstring path, int count);
	void SetButtons(Vector2 startPos, Vector2 space);
	vector<shared_ptr<GameObject>> _items;
};

