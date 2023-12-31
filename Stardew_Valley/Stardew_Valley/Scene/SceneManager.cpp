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

	_escUI = make_shared<EscapeUI>(this);
}

void SceneManager::Update()
{
	_cover->Update();
	_escUI->Update();
	_scenes[_index]->Update();

	if (KEY_DOWN(VK_ESCAPE) && _index != SceneIndex::LOGO)
		_escUI->SwitchActive();

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

	_escUI->PostRender();
	_cover->PostRender();
}

void SceneManager::ChangeScene(int index)
{
	_index = index;
	_scenes[_index]->Initialize();
}
