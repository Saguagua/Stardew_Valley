#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();


	static bool _debug;
private:
	void Initialize();

	shared_ptr<Scene> _scene;
};