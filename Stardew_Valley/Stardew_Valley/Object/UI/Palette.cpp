#include "framework.h"
#include "Palette.h"

Palette* Palette::_instance = nullptr;

Palette::Palette(Vector2 size)
	:_size(size)
{
	_map = make_shared<TileMap>(DATA->GetInitialMapInfos());
	_map->ChangeMap(0);

	_mainRect = make_shared<ColorButton>(PURPLE, _size);
	CallBack onEvent = std::bind(&Palette::Move, this);
	_mainRect->SetMouseOnEvent(onEvent);

	CallBackBool onEvent2 = std::bind(&Palette::OnFocus, this, std::placeholders::_1);
	_mainRect->SetMouseOnEvent(onEvent2);

	CreateChartButtons();
	CreateTileList();
	CreateObjectList();
	CreateLoadList();

	_lists[TILE]->SetActive(true);
}

void Palette::Render()
{
	_map->Render();
}

void Palette::PostRender()
{
	_mainRect->Render();

	for (auto button : _chartButtons)
		button->Render();

	for (auto list : _lists)
		list->Render();
}

void Palette::Update()
{
	_mainRect->Update();

	for (auto button : _chartButtons)
		button->Update();

	for (auto list : _lists)
		list->Update();

	KeyInput();
}

void Palette::Move()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = S_MOUSE_POS - _mainRect->GetTransform()->GetPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_mainRect->GetTransform()->SetPos(S_MOUSE_POS - _centerToMouse);
	}
}

void Palette::ChartButtonEvent(int index)
{
	_chartIndex = index;

	switch (_chartIndex)
	{
	case ChartType::TILE:
	{
		_lists[TILE]->SetActive(true);
		_lists[OBJECT]->SetActive(false);
		_lists[LOAD]->SetActive(false);
		break;
	}
	case ChartType::OBJECT:
	{
		_lists[TILE]->SetActive(false);
		_lists[OBJECT]->SetActive(true);
		_lists[LOAD]->SetActive(false);

		break;
	}
	case ChartType::LOAD:
	{
		_lists[TILE]->SetActive(false);
		_lists[OBJECT]->SetActive(false);
		_lists[LOAD]->SetActive(true);
		
		break;
	}
	case ChartType::SAVE:
	{
		DATA->MapToolSave();
		break;
	}
	default:
		break;
	}
}

void Palette::ChangeMap(int index)
{
	if (_lists[LOAD]->GetCurIndex() == index)
		return;

	_map->ChangeMap(index);
}

void Palette::CreateChartButtons()
{
	Vector2 halfSize = _size * 0.5f;
	Vector2 buttonSize = _size * 0.1f;
	float space = (_size.x - buttonSize.x * 4) / 5;

	shared_ptr<TextureButton>  button = make_shared<TextureButton>("TileButton", buttonSize);
	shared_ptr<TextureButton> button2 = make_shared<TextureButton>("HorseRadish", buttonSize);
	shared_ptr<TextureButton> button3 = make_shared<TextureButton>("FileButton", buttonSize);
	shared_ptr<TextureButton> button4 = make_shared<TextureButton>("SaveButton", buttonSize);

	button->GetTransform()->SetPos(Vector2(-halfSize.x + space, halfSize.y - buttonSize.y * 0.6f));
	button2->GetTransform()->SetPos(Vector2(-halfSize.x + space * 2 + buttonSize.x, halfSize.y - buttonSize.y * 0.6f));
	button3->GetTransform()->SetPos(Vector2(-halfSize.x + space * 3 + buttonSize.x * 2, halfSize.y - buttonSize.y * 0.6f));
	button4->GetTransform()->SetPos(Vector2(-halfSize.x + space * 4 + buttonSize.x * 3, halfSize.y - buttonSize.y * 0.6f));

	button->GetTransform()->SetParent(_mainRect->GetTransform());
	button2->GetTransform()->SetParent(_mainRect->GetTransform());
	button3->GetTransform()->SetParent(_mainRect->GetTransform());
	button4->GetTransform()->SetParent(_mainRect->GetTransform());

	CallBackInt cb = std::bind(&Palette::ChartButtonEvent, this, 0);
	button->SetPushEvent(cb);
	cb = std::bind(&Palette::ChartButtonEvent, this, 1);
	button2->SetPushEvent(cb);
	cb = std::bind(&Palette::ChartButtonEvent, this, 2);
	button3->SetPushEvent(cb);
	cb = std::bind(&Palette::ChartButtonEvent, this, 3);
	button4->SetPushEvent(cb);

	_chartButtons.push_back(button);
	_chartButtons.push_back(button2);
	_chartButtons.push_back(button3);
	_chartButtons.push_back(button4);
}

void Palette::CreateTileList()
{
	auto tileInfo = DATA->GetTileInfos();
	vector<string> names;

	for (pair<string, int> tile : tileInfo)
	{
		names.push_back(tile.first);
	}

	shared_ptr<List> list = make_shared<List>(_size * 0.9f, Vector2(5, 3), names);
	list->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	list->SetParent(_mainRect->GetTransform());

	_lists.push_back(list);
}

void Palette::CreateObjectList()
{
	auto deployInfo = DATA->GetDeployInfos();
	vector<string> names;

	for (auto info : deployInfo)
	{
		names.push_back(info.first);
	}

	shared_ptr<List> list = make_shared<List>(_size * 0.9f, Vector2(5, 9), names);
	list->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	list->SetParent(_mainRect->GetTransform());
	list->SetActive(false);

	_lists.push_back(list);
}

void Palette::CreateLoadList()
{
	_mapInfos = DATA->GetInitialMapInfos();
	vector<string> names;

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		names.push_back(to_string(i));
	}

	shared_ptr<List> list = make_shared<List>(_size * 0.9f, Vector2(_mapInfos.size(), 5), names);

	vector<CallBackInt> cbs;

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		CallBackInt cb = std::bind(&Palette::ChangeMap, this, i);
		cbs.push_back(cb);
	}

	list->AddCallBackInt(cbs);
	list->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	list->SetParent(_mainRect->GetTransform());
	list->SetActive(false);

	_lists.push_back(list);
}

void Palette::KeyInput()
{
	if (_mainRect->GetFocus())
		return;

	if (KEY_PRESS(VK_LBUTTON))
	{
		if (_lists[_chartIndex]->GetCurIndex() != -1)
			_map->ChangeTile(W_MOUSE_POS, _chartIndex, _lists[_chartIndex]->GetCurBotton()->GetName());
	}
}
