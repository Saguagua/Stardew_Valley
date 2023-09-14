#pragma once

class BagUI :public List, PlayerSubscribe
{
public:
	BagUI(shared_ptr<PlayerImproved> player);
	~BagUI() {}

	void Update();
	void Render();

	virtual void UpdateInfo() override;
	virtual void Dead() override;
private:
	void CreateButtons();

	void ClickItem(int index);
	shared_ptr<Transform> _objSlot;
	shared_ptr<Sprite> _obj;
	shared_ptr<NumberUI> _number;

	int _selectedIndex = -1;
};

