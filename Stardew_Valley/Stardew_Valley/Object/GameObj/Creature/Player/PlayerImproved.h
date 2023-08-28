#pragma once
class PlayerSubscribe;
class FishingMinigame;
class FishingHook;

class PlayerImproved: public Player
{
public:
	PlayerImproved();
	~PlayerImproved() {}

	virtual void Update() override;
	virtual void Render() override;

	void PlayAction();

	void RequestSubscribe(PlayerSubscribe* subscriber);
	void CancelSubscribe(PlayerSubscribe* subscriber);

	void KeyInput();

	void AddMaxHP(short cost);
	void AddMaxStamina(short cost);
	virtual void AddHP(short cost) override;
	void AddStamina(short cost);
	bool AddItem(string name);

	void SetCurItem(int index);
	void SwapItems(int index1, int index2);

	void SetFishing(bool val) { _isFishing = val; }

	void ActiveFishingHook(Vector2 originPos, Vector2 direction, float power);
	bool IsHookLanded() { return _hook->IsLanded(); }
	Vector2 GetHookPos() { return _hook->GetWorldPos(); }
private:
	void ItemAction();
	virtual void SetPause(bool val) override;

	void SendToSubscribers(int type);

	list<PlayerSubscribe*> _subscribers;
	shared_ptr<FishingHook> _hook;
	shared_ptr<FishingMinigame> _fishing;
	bool _isFishing = false;
};

