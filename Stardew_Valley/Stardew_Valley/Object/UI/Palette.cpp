#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainWin = make_shared<ColorButton>(PURPLE, _size);
	_tileList = make_shared<List>(_size * 0.90f, L"Resource/Tile/TileBright.png", Vector2(13, 14));

	_tileList->GetTransform()->SetPos(Vector2(0.0f, -20.0f));
	_tileList->SetParent(_mainWin->GetTransform());

	CallBack onEvent = std::bind(&Palette::Move, this);
	_mainWin->SetMouseOnEvent(onEvent);

	CallBackBool onEvent2 = std::bind(&Palette::OnFocus, this, std::placeholders::_1);
	_mainWin->SetMouseOnEvent(onEvent2);

	CreateChartButtons();
}

void Palette::PostRender()
{
	_mainWin->Render();
	for (auto button : _chartButtons)
		button->Render();
	_tileList->Render();
}

void Palette::Update()
{
	_mainWin->Update();
	for (auto button : _chartButtons)
		button->Update();

	_tileList->Update();
}

void Palette::Move()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = S_MOUSE_POS - _mainWin->GetTransform()->GetPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_mainWin->GetTransform()->SetPos(S_MOUSE_POS - _centerToMouse);
	}
}

void Palette::ChageChart(int index)
{
	switch (index)
	{
	case 0:
	{
		_tileList->SetActive(true);
		break;
	}
	case 1:
	{
		_tileList->SetActive(false);
		break;
	}
	case 2:
	{

		break;
	}
	default:
		break;
	}
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

	button->GetTransform()->SetParent(_mainWin->GetTransform());
	button2->GetTransform()->SetParent(_mainWin->GetTransform());
	button3->GetTransform()->SetParent(_mainWin->GetTransform());

	CallBackInt cb = std::bind(&Palette::ChageChart, this, 0);
	button->SetPushEvent(cb);
	cb = std::bind(&Palette::ChageChart, this, 1);
	button2->SetPushEvent(cb);

	_chartButtons.push_back(button);
	_chartButtons.push_back(button2);
	_chartButtons.push_back(button3);
}
