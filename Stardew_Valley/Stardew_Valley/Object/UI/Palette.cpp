#include "framework.h"
#include "../../Data/MapInfo.h"
#include "List.h"
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
		DATA->Save();
		break;
	}
	default:
		break;
	}
}

void Palette::ChangeMap(int index)
{
	if (_saveList->GetCurIndex() == index)
		return;

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
	Vector2 maxFrame = DATA->GetTileMaxFrame();

	_tileList = make_shared<List>(L"Resource/Tile/Tile.png", _size * 0.9f, maxFrame, maxFrame.x * maxFrame.y);
	_tileList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_tileList->SetParent(_mainRect->GetTransform());
}

void Palette::CreateObjectList()
{
	Vector2 maxFrame = DATA->GetObjectMaxFrame();
	
	_objectList = make_shared<List>(L"Resource/Object/Objects.png", _size * 0.9f, maxFrame, maxFrame.x * maxFrame.y);
	_objectList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_objectList->SetParent(_mainRect->GetTransform());
	_objectList->SetActive(false);
}

void Palette::CreateSaveList()
{
	_mapInfos = DATA->GetMapInfos();
	_saveList = make_shared<List>(L"Resource/Tile/Tile.png", _size * 0.9f, Vector2(_mapInfos.size(), 1), _mapInfos.size());

	vector<CallBackInt> cbs;

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		CallBackInt cb = std::bind(&Palette::ChangeMap, this, i);
		cbs.push_back(cb);
	}
	_saveList->AddCallBackInt(cbs);
	_saveList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_saveList->SetParent(_mainRect->GetTransform());
	_saveList->SetActive(false);
}
