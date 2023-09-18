#pragma once
class MapToolScene :public Scene
{
public:
	MapToolScene();
	~MapToolScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void Initialize() override;
	virtual void WhenCoverDark() override;

private:
};