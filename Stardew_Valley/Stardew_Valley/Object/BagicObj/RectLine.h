#pragma once
#include "ShapeLine.h"

class RectLine :public ShapeLine
{

public:
	RectLine(Vector2 size);
	virtual ~RectLine() {}

private:
	virtual void CreateVertices() override;

	Vector2 _size = {1, 1};
};

