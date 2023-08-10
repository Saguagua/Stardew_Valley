#pragma once
class DataScene:public Scene
{
public:
	DataScene();
	virtual ~DataScene();

	virtual void Update() override;
	virtual void Render() override;
};

