#pragma once
class NormalScene :public Scene
{
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

