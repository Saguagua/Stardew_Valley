#pragma once
class DropItem :public DeployableObject
{
public:
	DropItem();
	virtual ~DropItem() {}

	void Update();
	void Render();

	virtual void Interaction() override;
	virtual void Spawn(string name, vector<short> vals) override;
	void AddPos(Vector2 pos) { _col->AddPos(pos); }

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	shared_ptr<CircleCollider> GetArea() { return _dragArea; }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }

private:
	shared_ptr<CircleCollider> _col;
	shared_ptr<CircleCollider> _dragArea;
	string _itemName;

};

