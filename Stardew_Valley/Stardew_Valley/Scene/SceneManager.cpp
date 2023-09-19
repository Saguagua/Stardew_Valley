#include "framework.h"
#include "Main/LogoScene.h"
#include "Main/DayFinishScene.h"
#include "MapTool/MapToolScene.h"
#include "TestScene/TestScene.h"
#include "TestScene\ColliderScene.h"
#include "InGame/NormalScene.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_scenes.push_back(make_shared<LogoScene>());
	_scenes.push_back(make_shared<MapToolScene>());
	_scenes.push_back(make_shared<TestScene>());
	_scenes.push_back(make_shared<DayFinishScene>());

	_cover = make_shared<FrontCover>();

}

void SceneManager::Update()
{
	_cover->Update();

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


		if (tmp != _index)
		{
			ChangeScene(tmp);
		}

		ImGui::EndMenu();
	}

	_cover->PostRender();
}

void SceneManager::ChangeScene(int index)
{
	_index = index;
	_scenes[_index]->Initialize();
}
