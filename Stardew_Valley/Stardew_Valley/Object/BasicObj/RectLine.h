#pragma once
#include "ShapeLine.h"

class RectLine :public ShapeLine
{

public:
	RectLine(Vector2 size, );// 타입 만들기
	virtual ~RectLine() {}

private:
	virtual void CreateVertices() override;

	Vector2 _size = {1, 1};
};

