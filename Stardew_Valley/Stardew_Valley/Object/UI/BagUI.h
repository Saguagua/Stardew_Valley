#pragma once

class BagUI :public List, PlayerSubscribe
{
public:
	BagUI();
	virtual ~BagUI() {}

	void Update();
	void Render();

	virtual void UpdateInfo() override;
	virtual void Dead() override;

private:
	void CreateButtons();

	void ClickItem(int index);

	shared_ptr<Transform> _objSlot;
	shared_ptr<TextureRect> _obj;

	int _selectedIndex = -1;

};

