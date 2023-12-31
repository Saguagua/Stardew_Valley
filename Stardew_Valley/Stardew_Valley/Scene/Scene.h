#pragma once
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender() {}
	virtual void Initialize() abstract;
	virtual void WhenCoverDark() abstract;
};

