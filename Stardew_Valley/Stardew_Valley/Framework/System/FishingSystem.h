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
	void ActiveFishingHook(Vector2 direction, float power);
	void CheckTile();
	void EndMinigame(string name);

	Step GetStep() { return _step; }
private:
	static FishingSystem* _instance;


	shared_ptr<FishingMinigame> _minigame;
	shared_ptr<FishingHook> _hook;

	weak_ptr<PlayerImproved> _player;
	weak_ptr<TileMap> _map;
	bool _isActive = false;
	string _fishName = "BLANK";

	Step _step = Step::THROW;
};

