#pragma once
class NormalScene :public Scene
{
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

