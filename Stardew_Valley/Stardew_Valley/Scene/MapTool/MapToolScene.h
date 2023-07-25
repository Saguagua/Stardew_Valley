#pragma once
class MapToolScene :public Scene
{
public:
	MapToolScene();
	virtual ~MapToolScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

};