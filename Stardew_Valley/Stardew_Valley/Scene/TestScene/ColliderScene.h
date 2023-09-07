#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	~ColliderScene() {}

	virtual void Update() override;
	virtual void Render() override;

	virtual void Initialize() override;
private: 
	shared_ptr<CircleCollider> _circle;
	shared_ptr<CircleCollider> _circle2;
	shared_ptr<RectCollider> _rect;
	shared_ptr<RectCollider> _rect2;
};

