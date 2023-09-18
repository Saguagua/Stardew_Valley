#include "framework.h"
#include "Framework/Animation/Action.h"
#include "Box.h"

Box::Box(string name, Vector2 pos)
	:DeployableObject(DeployableObject::Type::BOX, name, pos)
{
	vector<Vector2> index;

	index.push_back(Vector2(0,0));
	index.push_back(Vector2(1,0));
	index.push_back(Vector2(2,0));
	index.push_back(Vector2(3,0));
	index.push_back(Vector2(4,0));
	index.push_back(Vector2(5,0));
	index.push_back(Vector2(6,0));
	index.push_back(Vector2(7,0));
	index.push_back(Vector2(8,0));
	index.push_back(Vector2(9,0));
	index.push_back(Vector2(10,0));
	index.push_back(Vector2(11,0));
	index.push_back(Vector2(12,0));

	_action = make_shared<Action>(index, Action::Type::END);
}

void Box::Interaction()
{
	if (!PLAYERUI->GetBagActive())
	{
		if (KEY_DOWN(VK_RBUTTON))
		{
			_action->SetRepeatType(Action::Type::END);
			_action->Play();
			PLAYERUI->SetSaleMode(true);
		}
	}
	else
	{
		if (KEY_DOWN(VK_RBUTTON))
		{
			_action->SetRepeatType(Action::Type::REVERSE_END);
			_action->Play();
			PLAYERUI->SetSaleMode(false);
		}
	}
	
}

vector<int> Box::GetProperty()
{
	return vector<int>(2, (0,0));
}

void Box::Update()
{
	_action->Update();
	_imgIndex = _action->GetCurFrame().x;
}
