#pragma once
#include "framework.h"
class LightInfo
{
public:
	LightInfo(XMFLOAT4 color, XMFLOAT4 pos) : _color(color), _pos(pos) {}
	~LightInfo() {}

	void SetColor(XMFLOAT4 color) { _color = color; }
	void SetPos(XMFLOAT4 pos) { _pos = pos; }

	XMFLOAT4 GetColor() { return _color; }
	XMFLOAT4 GetPos() { return _pos; }

private:
	XMFLOAT4 _color;
	XMFLOAT4 _pos;
};