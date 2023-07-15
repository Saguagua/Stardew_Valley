#pragma once
class Character
{
public:
	Character();
	~Character() {}

	void Update();
	void Render();

	void KeyInput();

	void SetDebug(bool val) { _collider->SetDebug(val);}
	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	Vector2 GetWorldPos();
private:
	shared_ptr<Transform> _quadSlot;
	shared_ptr<CircleCollider> _collider;
	shared_ptr<TextureRect> _quad;
};

