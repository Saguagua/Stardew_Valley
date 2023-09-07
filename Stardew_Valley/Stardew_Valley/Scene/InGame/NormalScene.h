#pragma once
class NormalScene :public Scene
{
public:
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

