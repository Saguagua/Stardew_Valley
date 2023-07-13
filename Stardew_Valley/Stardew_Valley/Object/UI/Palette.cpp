#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainRect = make_shared<ColorButton>(PURPLE, _size);
	CallBack onEvent = std::bind(&Palette::Move, this);
	_mainRect->SetMouseOnEvent(onEvent);

	CallBackBool onEvent2 = std::bind(&Palette::OnFocus, this, std::placeholders::_1);
	_mainRect->SetMouseOnEvent(onEvent2);

	CreateChartButtons();
	CreateTileList();
	CreateSaveList();
}

void Palette::PostRender()
{
	_mainRect->Render();

	for (auto button : _chartButtons)
		button->Render();

	_tileList->Render();
	_saveList->Render();
}

void Palette::Update()
{
	_mainRect->Update();
	for (auto button : _chartButtons)
		button->Update();

	_tileList->Update();
	_saveList->Update();
}

Vector2 Palette::GetCurTileFrame()
{
	int index = _tileList->GetCurIndex();
	if (index == -1)
		return Vector2(-1, -1);
	Vector2 maxFrame = SaveManager::GetInstance()->GetMaxFrame();

	return Vector2(index % (int)maxFrame.x, index / (int)maxFrame.x);
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

void Palette::ChageChart(int index)
{
	switch (index)
	{
	case 0:
	{
		_tileList->SetActive(true);
		_saveList->SetActive(false);
		break;
	}
	case 1:
	{
		_tileList->SetActive(false);
		_saveList->SetActive(true);
		
		break;
	}
	case 2:
	{
		shared_ptr<MapInfo> info = make_shared<MapInfo>("Farming", Vector2(50, 50), _tileMap.lock()->GetFrames());
		
		SaveManager::GetInstance()->SaveMap(info);

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

	
	_tileMap.lock()->LoadMap(_mapInfos[index]);
}

void Palette::CreateChartButtons()
{
	Vector2 buttonSize = _size * 0.05f;
	float space = (_size.x - buttonSize.x) / 4;
	shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Icons/Tiles.png", buttonSize);
	shared_ptr<TextureButton> button2 = make_shared<TextureButton>(L"Resource/Icons/file.png", buttonSize);
	shared_ptr<TextureButton> button3 = make_shared<TextureButton>(L"Resource/Icons/save.png", buttonSize);

	button->GetTransform()->SetPos(Vector2(-_size.x / 2 + buttonSize.x + space, _size.y/2 - buttonSize.y));
	button2->GetTransform()->SetPos(Vector2(0.0f, _size.y/2 - buttonSize.y));
	button3->GetTransform()->SetPos(Vector2(_size.x/2 - buttonSize.x - space, _size.y/2 - buttonSize.y));

	button->GetTransform()->SetParent(_mainRect->GetTransform());
	button2->GetTransform()->SetParent(_mainRect->GetTransform());
	button3->GetTransform()->SetParent(_mainRect->GetTransform());

	CallBackInt cb = std::bind(&Palette::ChageChart, this, 0);
	button->SetPushEvent(cb);
	cb = std::bind(&Palette::ChageChart, this, 1);
	button2->SetPushEvent(cb);
	cb = std::bind(&Palette::ChageChart, this, 2);
	button3->SetPushEvent(cb);

	_chartButtons.push_back(button);
	_chartButtons.push_back(button2);
	_chartButtons.push_back(button3);
}

void Palette::CreateTileList()
{
	vector<shared_ptr<TextureButton>> buttons;
	Vector2 frame = SaveManager::GetInstance()->GetMaxFrame();

	Vector2 buttonSize;
	buttonSize.x = _size.x * 0.9f / (frame.x + 1);
	buttonSize.y = _size.y * 0.9f / (frame.y + 1);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Tile/Tile.png", frame, buttonSize);
			buttons.push_back(button);
		}
	}

	_tileList = make_shared<List>(_size * 0.90f, buttons, frame);
	_tileList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_tileList->SetParent(_mainRect->GetTransform());
}

void Palette::CreateSaveList()
{
	_mapInfos = SaveManager::GetInstance()->GetMapInfos();
	vector<shared_ptr<TextureButton>> buttons;

	Vector2 buttonSize;
	buttonSize.x = _size.x * 0.9f / 7;
	buttonSize.y = _size.y * 0.9f / 7;

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Tile/Tile.png", Vector2(13, 7), buttonSize);
		CallBackBool cb = std::bind(&Palette::ChangeMap, this, std::placeholders::_1);
		button->SetPushEvent(cb);
		buttons.push_back(button);
	}

	_saveList = make_shared<List>(_size * 0.9f, buttons, Vector2(6,6));
	_saveList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_saveList->SetParent(_mainRect->GetTransform());
	_saveList->SetActive(false);
}
