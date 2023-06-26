#pragma once
#include "framework.h"

struct Vertex
{
	XMFLOAT3 pos;
};

struct VertexColor
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct VertexTexture
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};