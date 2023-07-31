#include "framework.h"
#include "../BasicObj/XMLRect.h"
#include "List.h"

void List::Render()
{
	if (!_isActive)
		return;
	_transform->Set_World(0);
	_body->Render();

	for (auto button : _buttons)
	{
		button->Render();
	}
}

void List::Update()
{
	_transform->Update();

	for (shared_ptr<TextureButton> button : _buttons)
	{
		button->Update();
	}
}

void List::SetButtons(Vector2 startPos, Vector2 space)
{
	Vector2 frame = _buttons[0]->GetMaxFrame();
	int index = 0;

	for (int i = 0; i < _matrix.y; i++)
	{
		for (int j = 0; j < _matrix.x; j++)
		{
			Vector2 pos;
			pos.x = startPos.x + space.x + j * (_buttonSize.x + space.x);
			pos.y = startPos.y - space.y + i * (_buttonSize.y - space.y);
			_buttons[index]->GetTransform()->SetPos(pos);
			_buttons[index]->GetTransform()->SetParent(_transform);
			_buttons[index]->SetFrame(Vector2(j, i));
			CallBackInt cb = std::bind(&List::PushButtonEvent, this, index);
			_buttons[index]->SetPushEvent(cb);
			_buttons[index]->SetLineColor(RED);
			index++;
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

				Vector2 curFrame = _buttons[i]->GetCurFrame();
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

				Vector2 curFrame = _buttons[i]->GetCurFrame();
				curFrame.y += 5;

				_buttons[i]->SetFrame(curFrame);
			}

			_buttons[i]->GetTransform()->SetPos(tmp);
		}
		
		InputManager::GetInstance()->SetMouseScroll(0);
	}
}
