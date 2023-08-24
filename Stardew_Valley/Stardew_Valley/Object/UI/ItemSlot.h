#pragma once
class ItemSlot : public List, PlayerSubscribe
{
public:
	ItemSlot(shared_ptr<PlayerImproved> player);
	~ItemSlot() {}

	void Update();

	void PushButtonEvent(int index);
	virtual void UpdateInfo() override;
	virtual void Dead() override;
private:
	void CreateButtons(wstring path, int count);

};

