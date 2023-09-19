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
	void Render();

	void PlayAction(int action);

	void RequestSubscribe(PlayerSubscribe* subscriber);
	void CancelSubscribe(PlayerSubscribe* subscriber);

	void KeyInput();

	void SetMap(shared_ptr<TileMap> map);

	void SetCurItem(int index);
	void SwapItems(shared_ptr<Item> item1, shared_ptr<Item> item2);

	bool AddItem(string name);
	void AddMaxHP(short cost);
	void AddMaxStamina(short cost);
	void AddHP(short cost);
	void AddStamina(short cost);

	void SetFreeze(bool val) { _freeze = val; }
	void SetToolActive(bool val) { _toolActive = val; }
	void SetAttacking(bool val) { _isAttacking = val; }
	void SendToSubscribers(int type);

	bool IsAttacking() { return _isAttacking; }
	shared_ptr<RectCollider> GetWeaponCollider() { return _weaponCollider; }

	void Kill();

protected:
	void CreateAction();
	void ChangeIndex();
	void ItemAction();
	void SetPause(bool val);

	void UpdateHandSlot();
	void UpdateCenterSlot();
	//CallBack
	void ToolEndEvent();
	void DeathEvent();
	void Return();
	CallBack _cb;

	weak_ptr<TileMap> _map;

	shared_ptr<Sprite> _itemRenderer;

	shared_ptr<RectCollider> _weaponCollider;

	vector<shared_ptr<Action>> _toolActions;

	//Slots
	shared_ptr<Transform> _centerSlot;
	shared_ptr<Transform> _itemSlot;
	shared_ptr<Transform> _handSlot;

	list<PlayerSubscribe*> _subscribers;
	bool _toolActive = false;
	int _itemActionIndex = 0;

	Vector2 _handSlotDirection;
	float _handSlotRotate;
	Vector2 _centerSlotDirection;
	float _centerSlotRotate;


	bool _isAttacking = false;
};

