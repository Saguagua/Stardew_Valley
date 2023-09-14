#pragma once
class PlayerSubscribe;
class FishingMinigame;
class FishingHook;

class PlayerImproved : public Player, public enable_shared_from_this<PlayerImproved>
{
public:
	PlayerImproved();
	~PlayerImproved() {}

	void Initialize();

	void Update();
	virtual void Render() override;

	void PlayAction(int action);

	void RequestSubscribe(PlayerSubscribe* subscriber);
	void CancelSubscribe(PlayerSubscribe* subscriber);

	void KeyInput();

	void SetMap(shared_ptr<TileMap> map);

	void SetCurItem(int index);
	void SwapItems(int index1, int index2);

	bool AddItem(string name);
	void AddMaxHP(short cost);
	void AddMaxStamina(short cost);
	virtual void AddHP(short cost) override;
	void AddStamina(short cost);

	void SetFreeze(bool val) { _freeze = val; }
	void SendToSubscribers(int type);

protected:
	virtual void CreateAction() override;
	void ChangeIndex();
	void ItemAction();
	virtual void SetPause(bool val) override;

	void UpdateHandSlot();
	//CallBack
	void ToolEndEvent();

	weak_ptr<TileMap> _map;

	shared_ptr<Sprite> _itemRenderer;


	vector<shared_ptr<Action>> _toolActions;

	//Slots
	shared_ptr<Transform> _itemSlot;
	shared_ptr<Transform> _handSlot;

	list<PlayerSubscribe*> _subscribers;
	bool _toolActive = false;
	int _itemActionIndex = 0;

	Vector2 _handSlotDirection;
	float _handSlotRotate;
};

