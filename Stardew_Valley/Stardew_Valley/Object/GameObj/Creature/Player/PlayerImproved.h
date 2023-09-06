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

	void SetCurItem(int index);
	void SwapItems(int index1, int index2);

	bool AddItem(string name);

	void SetFreeze(bool val) { _freeze = val; }
protected:
	void ChangeIndex();
	void ItemAction();
	virtual void SetPause(bool val) override;

	void SendToSubscribers(int type);

	list<PlayerSubscribe*> _subscribers;
};

