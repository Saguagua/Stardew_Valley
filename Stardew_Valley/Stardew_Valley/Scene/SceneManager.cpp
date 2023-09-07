#include "framework.h"
#include "MapTool/MapToolScene.h"
#include "TestScene/TestScene.h"
#include "TestScene\ColliderScene.h"
#include "InGame/NormalScene.h"
#include "InGame/DungeonScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_scenes.push_back(make_shared<MapToolScene>());
	_scenes.push_back(make_shared<TestScene>());
	_scenes.push_back(make_shared<ColliderScene>());
	_scenes.push_back(make_shared<NormalScene>());
	_scenes.push_back(make_shared<DungeonScene>());
}

void SceneManager::Update()
{
	_scenes[_index]->Update();
}

void SceneManager::Render()
{
	_scenes[_index]->Render();
}

void SceneManager::PostRender()
{
	_scenes[_index]->PostRender();

	ImGui::SliderInt("Index", &_index, 0, _scenes.size()-1);
}

