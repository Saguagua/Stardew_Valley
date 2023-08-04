#pragma once
#include "../../Data/PlayerInfoSubscriber.h"
class BagUI :public List, PlayerInfoSubscriber
{
public:
	BagUI();
	virtual ~BagUI() {}

	void Update();
	void Render();
private:
	virtual void UpdatePlayerInfo() override;
	void CreateButtons();

	void ClickItem(int index);

	shared_ptr<Transform> _objSlot;
	shared_ptr<TextureRect> _obj;

	Vector2 _objMaxFrame;
	int _selectedIndex = -1;

};

