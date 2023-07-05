#pragma once
class TileManager
{
	TileManager() {}
	~TileManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new TileManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static TileManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	shared_ptr<TextureRect> GetTile(wstring path, Vector2 maxFrame, Vector2 size)
	{
		if (_table.count(path) == 0)
			_table[path] = make_shared<TextureRect>(path, maxFrame, size);

		return _table[path];
	}

private:
	static TileManager* _instance;

	unordered_map<wstring, shared_ptr<TextureRect>> _table;
};