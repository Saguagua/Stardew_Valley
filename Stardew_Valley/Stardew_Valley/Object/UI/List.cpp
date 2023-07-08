#include "framework.h"
#include "List.h"

List::List(Vector2 size, wstring path, Vector2 frame)
	:_size(size)
{
	_mainRect = make_shared<ColorButton>(LIGHTPURPLE, _size);
	
	CreateButtons(path, frame);
}

void List::Render()
{
	_mainRect->Render();

	for (shared_ptr<TextureButton> button : _buttons)
	{
		button->Render();
	}
}

void List::Update()
{
	_mainRect->Update();

	for (shared_ptr<TextureButton> button : _buttons)
	{
		button->Update();
	}
}

shared_ptr<TileInfo> List::GetCurTileInfo()
{
	if (_curIndex == -1)
		return nullptr;
	
	return _infos[_curIndex];
}

void List::CreateButtons(wstring path, Vector2 frame)
{
	Vector2 space;
	space.x = _size.x / frame.x / frame.x;
	space.y = _size.y / frame.y / frame.y;

	_buttonSize.x = 30;// _size.x / frame.x - 2 * space.x;
	_buttonSize.y = 30;// _size.y / frame.y - 2 * space.y;

	Vector2 startPos;
	startPos.x = -_size.x / 2 + _buttonSize.x/2;
	startPos.y = _size.y / 2 - _buttonSize.y/2;

	for (int i = 0; i < frame.y; i++)
	{
		for (int j = 0; j < frame.x; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(path, frame, _buttonSize);
			button->GetTransform()->SetPos(Vector2(startPos.x + j * (_buttonSize.x + space.x), startPos.y - i * (_buttonSize.y + space.y)));
			button->GetTransform()->SetParent(_mainRect->GetTransform());
			button->SetFrame(Vector2(j, i));
			CallBackInt pEvent = std::bind(&List::PushButtonEvent, this, j + i * (frame.x));
			button->SetPushEvent(pEvent);
			_buttons.push_back(button);

			shared_ptr<TileInfo> info = make_shared<TileInfo>(Vector2(0,0), Vector2(j, i), TileInfo::Type::MOVEABLE);
			_infos.push_back(info);
		}
	}
}

void List::PushButtonEvent(int index)
{
	if (_curIndex != -1)
		_buttons[_curIndex]->GetCollider()->SetDebug(false);
	if (_curIndex == index)
	{
		_curIndex = -1;
		return;
	}
	_curIndex = index;
	_buttons[_curIndex]->GetCollider()->SetDebug(true);
}

void List::Scroll()
{
	short val = MOUSE_SCROLL;

	if (val > 0)
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			Vector2 tmp = _buttons[i]->GetTransform()->GetPos();
			tmp += Vector2(0.0f, 1.0f) * DELTA_TIME * 1000.0f;

			if (tmp.y > _size.y / 2 + _buttonSize.y / 2)
			{
				tmp.y = -_size.y / 2 - _buttonSize.y / 2;

				Vector2 curFrame = _buttons[i]->GetFrame();
				curFrame.y -= 5;

				_buttons[i]->SetFrame(curFrame);
			}

			_buttons[i]->GetTransform()->SetPos(tmp);

		}
		InputManager::GetInstance()->SetMouseScroll(0);
	}
	else if (val < 0)
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			Vector2 tmp = _buttons[i]->GetTransform()->GetPos();
			tmp += Vector2(0.0f, -1.0f) * DELTA_TIME * 1000.0f;

			if (tmp.y < -_size.y / 2 - _buttonSize.y / 2)
			{
				tmp.y = _size.y / 2 + _buttonSize.y / 2;

				Vector2 curFrame = _buttons[i]->GetFrame();
				curFrame.y += 5;

				_buttons[i]->SetFrame(curFrame);
			}

			_buttons[i]->GetTransform()->SetPos(tmp);
		}
		
		InputManager::GetInstance()->SetMouseScroll(0);
	}
}
