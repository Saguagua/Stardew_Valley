#pragma once
//#include "../../Data/PlayerInfoSubscriber.h"
class BagUI :public List
{
public:
	BagUI();
	virtual ~BagUI() {}

	void Update();
	void Render();
private:
	void CreateButtons();

	void ClickItem(int index);

	shared_ptr<Transform> _objSlot;
	shared_ptr<TextureRect> _obj;
	shared_ptr<class PlayerInfo> _playerInfo;

	Vector2 _objMaxFrame;
	int _selectedIndex = -1;
	
};

