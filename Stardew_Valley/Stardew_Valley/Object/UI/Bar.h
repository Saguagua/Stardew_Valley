#pragma once
class Bar :public PlayerSubscribe
{
public:
	Bar(shared_ptr<PlayerImproved> player, string name, Vector2 size);
	~Bar() {}

	void Render();

	void SetRatio(Vector2 ratio);
	void SetPos(Vector2 pos);

	Vector2 GetPos() { return _bodyTransform->GetPos(); }

	virtual void UpdateInfo() override;
	virtual void Dead() override;
private:
	shared_ptr<Transform> _bodyTransform;
	shared_ptr<Transform> _guageTransform;
	shared_ptr<Sprite> _body;
	shared_ptr<SingleColorRect> _gauge;

	weak_ptr<PlayerImproved> _player;

};

