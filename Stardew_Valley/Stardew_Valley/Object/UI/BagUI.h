#pragma once

class BagUI :public List, PlayerSubscribe
{
public:
	BagUI(shared_ptr<PlayerImproved> player);
	~BagUI() {}

	void Update();
	void Render();

	void SetActive(bool val);

	virtual void UpdateInfo() override;
	virtual void Dead() override;

	void SetSaleMode(bool val);
	bool GetSaleMode() { return _saleMode; }
private:
	void CreateButtons();

	void ClickItem(int index);
	void ClickSaleButton();

	shared_ptr<Transform> _objSlot;
	shared_ptr<Sprite> _obj;
	shared_ptr<Sprite> _saleObj;
	shared_ptr<NumberUI> _number;
	shared_ptr<TextureButton> _saleButton;

	shared_ptr<Item> _selectedItem;
	shared_ptr<Item> _blankItem;

	bool _saleMode = false;
};

