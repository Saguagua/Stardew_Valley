#include "framework.h"
#include "NumberUI.h"

NumberUI::NumberUI(int num, int maxCount, Vector2 size)
	:_maxNumberCount(maxCount), _size(size)
{
	_number.resize(maxCount);

	Vector2 _singleSize = size;
	_singleSize.x = _size.x / maxCount;
	_renderer = make_shared<Sprite>("0", _singleSize, SpriteType::UI);

	_distance = _size.x / maxCount;
	_startPos = _distance * maxCount * -0.5f;

	_transform = make_shared<Transform>();

	SetNumber(num);
}

void NumberUI::Render()
{
	Vector2 pos;

	for (int i = 0; i < _number.size(); i++)
	{
		pos.x = _startPos + i * _distance;
		_transform->SetPos(_originPos + pos);
		_transform->Update();

		_transform->Set_World();
		_renderer->SetImage(_number[i]);
		_renderer->Render();
	}
}

void NumberUI::Update() // 숫자 변경할 때 애니메이션 추가
{
}

void NumberUI::SetNumber(int num)
{
	string tmp = to_string(num);

	if (tmp.size() > _number.size())
	{
		tmp = tmp.substr(tmp.length() - (tmp.size() - _number.size()));
	}
	else if (tmp.size() < _number.size())
	{
		while (tmp.size() < _number.size())
			tmp = " " + tmp;
	}

	for (int i = 0; i < _number.size(); i++)
	{
		if (tmp[i] == ' ')
			_number[i] = "BLANK";
		else
			_number[i] = std::string(1, tmp[i]);
	}
}
