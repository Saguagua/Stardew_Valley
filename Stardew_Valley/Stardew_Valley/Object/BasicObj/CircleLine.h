#pragma once
#include "ShapeLine.h"

class CircleLine :public ShapeLine
{
public:
	CircleLine(float radius);
	~CircleLine() {}


private:
	virtual void CreateVertices() override;

	float _radius;
};

