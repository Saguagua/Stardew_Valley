#pragma once
class DungeonScene :public Scene
{
public:
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
};

