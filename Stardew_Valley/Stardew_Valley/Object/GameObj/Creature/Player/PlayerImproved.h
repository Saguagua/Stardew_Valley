#pragma once
class PlayerSubscribe;
class FishingMinigame;
class FishingHook;

class PlayerImproved: public Player
{
public:
	PlayerImproved();
	~PlayerImproved() {}

	void Update();
	virtual void Render() override;

	void PlayAction(int action);

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

	void SetFreeze(bool val) { _freeze = val; }
private:
	void ChangeIndex();
	void ItemAction();
	virtual void SetPause(bool val) override;

	void SendToSubscribers(int type);

	list<PlayerSubscribe*> _subscribers;
};

