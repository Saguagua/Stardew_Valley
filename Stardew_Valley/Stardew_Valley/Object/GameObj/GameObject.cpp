#include "framework.h"
#include "GameObject.h"

GameObject::GameObject()
{
	_col = make_shared<CircleCollider>(20);
	_body = make_shared<TextureButton>(L"Resource/Object/Objects.png", Vector2(16, 6), Vector2(40, 40));
	
}

void GameObject::Update()
{
	_body->Update();
}

void GameObject::Render()
{
	_body->Render();
}

void GameObject::SetPos(Vector2 pos)
{
	_body->GetTransform()->SetPos(pos);
}

void GameObject::SetFrame(Vector2 frame)
{
	_body->SetFrame(frame);
}

bool GameObject::Block(shared_ptr<CircleCollider> other)
{
	return _body->GetCollider()->Block(other);
	//return _col->Block(other);
}

void GameObject::Spawn(Vector2 pos, Vector2 frame)
{
}
