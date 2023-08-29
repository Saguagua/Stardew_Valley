#pragma once
class FishingSystem
{
	

	FishingSystem();
	~FishingSystem() {}

public:

	enum Step
	{
	THROW,
	WAIT,
	HOLD,
	CATCH
	};

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new FishingSystem();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static FishingSystem* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return _instance;
	}

	void Update();
	void Render();

	void SetPlayer(shared_ptr<PlayerImproved> player);
	void SetMap(shared_ptr<TileMap> map) { _map = map; }

	void HookSetting(Vector2 direction, float power);
	void ActiveFishingHook();

	Step GetStep() { return _step; }

	void EndThrowing();
	void EndMinigame(bool result);
	void EndFishing(string itemName);
private:
	static FishingSystem* _instance;

	shared_ptr<FishingMinigame> _minigame;
	shared_ptr<FishingHook> _hook;

	weak_ptr<PlayerImproved> _player;
	weak_ptr<TileMap> _map;
	bool _isActive = false;
	string _fishName = "BLANK";

	float _waitCount = 0.0f;

	Step _step = Step::THROW;
};

