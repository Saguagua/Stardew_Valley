#include "framework.h"
#include "../../Data/MapInfo.h"
#include "Palette.h"

Palette* Palette::_instance = nullptr;

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainRect = make_shared<ColorButton>(PURPLE, _size);
	_mainRect->SetDebug(true);
	CallBack onEvent = std::bind(&Palette::Move, this);
	_mainRect->SetMouseOnEvent(onEvent);

	CallBackBool onEvent2 = std::bind(&Palette::OnFocus, this, std::placeholders::_1);
	_mainRect->SetMouseOnEvent(onEvent2);

	_tileMaxFrame = DATA->GetTileMaxFrame();
	_objectMaxFrame = DATA->GetObjectMaxFrame();

	CreateChartButtons();
	CreateTileList();
	CreateObjectList();
	CreateSaveList();
}

void Palette::PostRender()
{
	_mainRect->Render();

	for (auto button : _chartButtons)
		button->Render();

	_tileList->Render();
	_objectList->Render();
	_saveList->Render();
}

void Palette::Update()
{
	_mainRect->Update();

	for (auto button : _chartButtons)
		button->Update();

	_tileList->Update();
	_objectList->Update();
	_saveList->Update();
}

int Palette::GetCurTileCode()
{
	return _tileList->GetCurIndex();;
}

int Palette::GetCurObjectCode()
{
	return _objectList->GetCurIndex();
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
	case 0:
	{
		_tileList->SetActive(true);
		_objectList->SetActive(false);
		_saveList->SetActive(false);
		break;
	}
	case 1:
	{
		_tileList->SetActive(false);
		_objectList->SetActive(true);
		_saveList->SetActive(false);

		break;
	}
	case 2:
	{
		_tileList->SetActive(false);
		_objectList->SetActive(false);
		_saveList->SetActive(true);
		
		break;
	}
	case 3:
	{
		vector<shared_ptr<MapInfo>> infos = TILEMAP->GetMapInfo();
	
		DATA->SaveMaps(infos);

		break;
	}
	default:
		break;
	}
}

void Palette::ChangeMap(bool chosen)
{
	if (chosen)
		return;

	int index = _saveList->GetCurIndex();
	
	TILEMAP->ChangeMap(index);
}

void Palette::CreateChartButtons()
{
	Vector2 halfSize = _size * 0.5f;
	Vector2 buttonSize = _size * 0.05f;
	float space = (_size.x - buttonSize.x * 4) / 5;

	shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Icons/Tiles.png", buttonSize);
	shared_ptr<TextureButton> button2 = make_shared<TextureButton>(L"Resource/Icons/Tiles.png", buttonSize);
	shared_ptr<TextureButton> button3 = make_shared<TextureButton>(L"Resource/Icons/file.png", buttonSize);
	shared_ptr<TextureButton> button4 = make_shared<TextureButton>(L"Resource/Icons/save.png", buttonSize);

	button->GetTransform()->SetPos(Vector2(-halfSize.x + space, halfSize.y - buttonSize.y));
	button2->GetTransform()->SetPos(Vector2(-halfSize.x + space * 2 + buttonSize.x, halfSize.y - buttonSize.y));
	button3->GetTransform()->SetPos(Vector2(-halfSize.x + space * 3 + buttonSize.x * 2, halfSize.y - buttonSize.y));
	button4->GetTransform()->SetPos(Vector2(-halfSize.x + space * 4 + buttonSize.x * 3, halfSize.y - buttonSize.y));

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
	vector<shared_ptr<TextureButton>> buttons;

	Vector2 buttonSize;
	buttonSize.x = _size.x * 0.9f / (_tileMaxFrame.x + 1);
	buttonSize.y = _size.y * 0.9f / (_tileMaxFrame.y + 1);

	for (int i = 0; i < _tileMaxFrame.y; i++)
	{
		for (int j = 0; j < _tileMaxFrame.x; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Tile/Tile.png", _tileMaxFrame, buttonSize);
			buttons.push_back(button);
		}
	}
	_tileList = make_shared<List>(_size * 0.9f, buttons, _tileMaxFrame);
	_tileList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_tileList->SetParent(_mainRect->GetTransform());
}

void Palette::CreateObjectList()
{
	vector<shared_ptr<TextureButton>> buttons;

	Vector2 buttonSize;
	buttonSize.x = _size.x * 0.9f / (_objectMaxFrame.x + 1);
	buttonSize.y = _size.y * 0.9f / (_objectMaxFrame.y + 1);

	for (int i = 0; i < _objectMaxFrame.y; i++)
	{
		for (int j = 0; j < _objectMaxFrame.x; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Object/Objects.png", _objectMaxFrame, buttonSize);
			buttons.push_back(button);
		}
	}
	_objectList = make_shared<List>(_size * 0.9f, buttons, _objectMaxFrame);
	_objectList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_objectList->SetParent(_mainRect->GetTransform());
	_objectList->SetActive(false);
}

void Palette::CreateSaveList()
{
	_mapInfos = DATA->GetMapInfos();
	vector<shared_ptr<TextureButton>> buttons;

	Vector2 buttonSize;
	buttonSize.x = _size.x * 0.9f / 7;
	buttonSize.y = _size.y * 0.9f / 7;

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Tile/Tile.png", _tileMaxFrame, buttonSize);
		CallBackBool cb = std::bind(&Palette::ChangeMap, this, std::placeholders::_1);
		button->SetPushEvent(cb);
		buttons.push_back(button);
	}

	_saveList = make_shared<List>(_size * 0.9f, buttons, Vector2(6,6));
	_saveList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_saveList->SetParent(_mainRect->GetTransform());
	_saveList->SetActive(false);
}
