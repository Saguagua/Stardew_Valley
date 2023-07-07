#include "framework.h"
#include "List.h"

List::List(Vector2 size, wstring path, Vector2 frame)
	:_size(size), _maxFrame(frame)
{
	_mainRect = make_shared<ColorButton>(LIGHTPURPLE, _size);
	
	CreateButtons(path, _maxFrame);
	CallBack scroll = std::bind(&List::Scroll, this);
	_mainRect->SetScrollEvent(scroll);
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

void List::CreateButtons(wstring path, Vector2 frame)
{
	_buttonSize.x = _size.x / 5.0f;
	_buttonSize.y = _size.y / 5.0f;

	Vector2 startPos;
	startPos.x = -_size.x / 2 + _buttonSize.x;
	startPos.y = _size.y / 2 - _buttonSize.y;

	for (int i = 0; i <= frame.x; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(path, frame, _buttonSize);
			button->GetTransform()->SetPos(Vector2(startPos.x + i * (_buttonSize.x + _buttonSize.x/2), startPos.y - j * (_buttonSize.y + _buttonSize.y/2)));
			button->GetTransform()->SetParent(_mainRect->GetTransform());
			button->SetFrame(Vector2(i, j));
			//CallBackInt pEvent = std::bind(&List::PushButtonEvent, this, j + i * 3);
			//button->SetPushEvent(pEvent);
			_buttons.push_back(button);
		}
	}

}

void List::PushButtonEvent(int index)
{
	if (_curIndex != -1)
		_buttons[_curIndex]->GetCollider()->SetDebug(false);
	if (_curIndex == index)
		return;
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
