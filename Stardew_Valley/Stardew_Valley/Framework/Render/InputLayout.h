#pragma once
#include "framework.h"

struct Vertex
{
	XMFLOAT3 pos;
};


struct VertexTexture
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

struct VertexLight
{
	XMFLOAT3 pos;
	XMFLOAT4 light;
	XMFLOAT2 uv;
};