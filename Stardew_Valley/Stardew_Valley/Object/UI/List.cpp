#include "framework.h"
#include "List.h"

List::List(wstring path, Vector2 size, Vector2 matrix, vector<string> names)
	:_size(size), _matrix(matrix)
{
	_transform = make_shared<Transform>();
	_body = make_shared<Sprite>(XMLPATH, "BLANK", _size, SpriteType::UI);
	CreateButtons(path, names);

	Vector2 space;
	space.x = (_size.x - _buttonSize.x * matrix.x) / (matrix.x + 1);
	space.y = (_size.y - _buttonSize.y * matrix.y) / (matrix.y + 1);
	Vector2 startPos;
	startPos.x = _size.x * -0.5f + space.x + _buttonSize.x * 0.5f;
	startPos.y = _size.y * 0.5f - space.y - _buttonSize.y * 0.5f;
	
	SetButtons(startPos, space);
}

void List::Render()
{
	if (!_isActive)
		return;

	_transform->Set_World(0);
	_body->Render();

	for (auto button : _buttons)
	{
		button->PostRender();
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

void List::AddCallBack(vector<CallBack> cbs)
{
	for (int i = 0; i < cbs.size(); i++)
	{
		_buttons[i]->AddPushEvent(cbs[i]);
	}
}

void List::AddCallBackInt(vector<CallBackInt> cbs)
{
	for (int i = 0; i < cbs.size(); i++)
	{
		_buttons[i]->AddPushEvent(cbs[i]);
	}
}

void List::CreateButtons(wstring path, vector<string> names)
{
	_buttonSize.x = _size.x * 0.9f / (_matrix.x + 1);
	_buttonSize.y = _size.y * 0.9f / (_matrix.y + 1);

	for (int i = 0; i < names.size(); i++)
	{
		shared_ptr<TextureButton> button = make_shared<TextureButton>(path, names[i], _buttonSize);
		_buttons.push_back(button);
	}
}

void List::SetButtons(Vector2 startPos, Vector2 space)
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < _buttons.size(); i++)
	{
		Vector2 pos;
		pos.x = startPos.x + x * (_buttonSize.x + space.x);
		pos.y = startPos.y - y * (_buttonSize.y + space.y);
		_buttons[i]->SetPos(pos);
		_buttons[i]->GetTransform()->SetParent(_transform);
		CallBackInt cb = std::bind(&List::PushButtonEvent, this, i);
		_buttons[i]->SetPushEvent(cb);
		_buttons[i]->SetLineColor(RED);
		x++;

		if (x == _matrix.x)
		{
			x = 0;
			y++;
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

				/*Vector2 curFrame = _buttons[i]->GetCurFrame();
				curFrame.y -= 5;

				_buttons[i]->SetFrame(curFrame);*/
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

				/*Vector2 curFrame = _buttons[i]->GetCurFrame();
				curFrame.y += 5;

				_buttons[i]->SetFrame(curFrame);*/
			}

			_buttons[i]->GetTransform()->SetPos(tmp);
		}
		
		InputManager::GetInstance()->SetMouseScroll(0);
	}
}
