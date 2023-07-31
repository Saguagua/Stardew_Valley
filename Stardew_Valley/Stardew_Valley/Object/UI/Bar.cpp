#include "framework.h"
#include "../BasicObj/XMLRect.h"
#include "Bar.h"

Bar::Bar(string path, string name, Vector2 size)
{
	_bodyTransform = make_shared<Transform>();
	_guageTransform = make_shared<Transform>();
	_body = make_shared<XMLRect>(path, name, size);
	_gauge = make_shared<XMLRect>(path, "FishingGameCursor.png", size - Vector2(10, 55));

	_guageTransform->SetPos(Vector2(0, -20));
	_guageTransform->SetAngle(PI);
	_guageTransform->SetParent(_bodyTransform);
}

void Bar::Render()
{
	_bodyTransform->Set_World();
	_body->Render();
	_guageTransform->Set_World();
	_gauge->Render();
}

void Bar::SetRatio(Vector2 ratio)
{
	_gauge->SetRatio(ratio);
}

void Bar::SetPos(Vector2 pos)
{
	_bodyTransform->SetPos(pos);
	_bodyTransform->Update();
	_guageTransform->Update();
}
