#include "framework.h"
#include "MapTool/MapToolScene.h"
#include "TestScene/TestScene.h"
#include "TestScene\ColliderScene.h"
#include "InGame/NormalScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_scenes.push_back(make_shared<MapToolScene>());
	_scenes.push_back(make_shared<TestScene>());
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

	if (ImGui::BeginMenu("SceneManager"))
	{
		int tmp = _index;
		ImGui::SliderInt("Index", &tmp, 0, _scenes.size() - 1);
		ImGui::Checkbox("Cover", &_changeScene);


		if (tmp != _index)
		{
			_index = tmp;
			_scenes[_index]->Initialize();
		}

		ImGui::EndMenu();
	}
}

