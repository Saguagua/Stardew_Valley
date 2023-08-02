#pragma once
class LightTestScene:public Scene
{
public:
	LightTestScene();
	virtual ~LightTestScene();
	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<class LightTextureRect> renderer;
	shared_ptr<TextureRect> trenderer;
	shared_ptr<CircleCollider> collider1;
	shared_ptr<CircleCollider> collider2;
	shared_ptr<CircleCollider> collider3;
	shared_ptr<CircleCollider> collider4;
};

