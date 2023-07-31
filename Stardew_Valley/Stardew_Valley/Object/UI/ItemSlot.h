#pragma once
class ItemSlot : public List
{
public:
	ItemSlot();
	virtual ~ItemSlot() {}

	virtual void Update() override;

	virtual void PushButtonEvent(int index) override;

private:
	virtual void CreateButtons(wstring path, int count) override;
	virtual void SetButtons(Vector2 startPos, Vector2 space) override;
	vector<shared_ptr<GameObject>> _items;
};

