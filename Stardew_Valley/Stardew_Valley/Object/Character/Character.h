#pragma once
class Character
{
public:

	Character();
	~Character() {}

	void Update();
	void Render();

	void KeyInput();

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

private:
	shared_ptr<Transform> _quadSlot;
	shared_ptr<CircleCollider> _collider;
	shared_ptr<Quad> _quad;
};

