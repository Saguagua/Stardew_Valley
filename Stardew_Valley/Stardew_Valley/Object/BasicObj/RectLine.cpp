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

	v.pos = { 0, _size.y, 0.0f }; // ���� ��
	_vertices.push_back(v);

	v.pos = { _size.x, _size.y, 0.0f }; // ������ ��
	_vertices.push_back(v);

	v.pos = { _size.x, 0, 0.0f }; // ������ �Ʒ�
	_vertices.push_back(v);

	v.pos = { 0, 0, 0.0f }; // ���� �Ʒ�
	_vertices.push_back(v);

	v.pos = { 0, _size.y, 0.0f }; // ���� ��
	_vertices.push_back(v);
}