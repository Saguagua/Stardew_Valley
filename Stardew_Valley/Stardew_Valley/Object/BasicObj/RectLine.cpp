#include "framework.h"
#include "RectLine.h"

RectLine::RectLine(Vector2 size)
	:_size(size)
{
	CreateVertices();
	CreateData();
	
	_cBuffer->SetColor(GREEN);
	_cBuffer->Update();
}


void RectLine::CreateVertices()
{
	Vertex v = {};

	v.pos = { 0, _size.y, 0.0f }; // 왼쪽 위
	_vertices.push_back(v);

	v.pos = { _size.x, _size.y, 0.0f }; // 오른쪽 위
	_vertices.push_back(v);

	v.pos = { _size.x, 0, 0.0f }; // 오른쪽 아래
	_vertices.push_back(v);

	v.pos = { 0, 0, 0.0f }; // 왼쪽 아래
	_vertices.push_back(v);

	v.pos = { 0, _size.y, 0.0f }; // 왼쪽 위
	_vertices.push_back(v);
}