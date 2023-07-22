#include "framework.h"
#include "List.h"

List::List(Vector2 size, vector<shared_ptr<TextureButton>> buttons, Vector2 matrix)
	:_size(size), _matrix(matrix)
{
	_transform = make_shared<Transform>();
	_mainRect = make_shared<SingleColorRect>(_size, GRAY);
	_buttons = buttons;
	_buttonSize = _buttons[0]->GetSize();
	SetButtons();
}

void List::Render()
{
	if (!_isActive)
		return;
	_transform->Set_World(0);
	_mainRect->Render();

	for (auto button : _buttons)
	{
		button->Render();
	}
}

void List::Update()
{
	if (!_isActive)
		return;

	_transform->Update();

	for (shared_ptr<TextureButton> button : _buttons)
	{
		button->Update();
	}
}

void List::SetButtons()
{
	Vector2 frame = _buttons[0]->GetMaxFrame();

	Vector2 space;
	space.x = _buttonSize.x / _matrix.x;
	space.y = _buttonSize.y / _matrix.y;

	int x = 0;
	int y = 0;

	for (int i = 0; i < _buttons.size(); i++)
	{
		Vector2 pos;
		pos.x = x * (_buttonSize.x + space.x);
		pos.y = _size.y - _buttonSize.y - y * (_buttonSize.y + space.y);

		_buttons[i]->GetTransform()->SetPos(pos);
		_buttons[i]->GetTransform()->SetParent(_transform);
		_buttons[i]->SetFrame(Vector2(x,y));
		CallBackInt cb = std::bind(&List::PushButtonEvent, this, x + y * frame.x);
		_buttons[i]->SetPushEvent(cb);

		x = (x + 1) % (int)frame.x;
		if (x == 0)
			y++;
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
