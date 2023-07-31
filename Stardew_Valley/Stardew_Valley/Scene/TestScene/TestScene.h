#pragma once
class TestScene :public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
};