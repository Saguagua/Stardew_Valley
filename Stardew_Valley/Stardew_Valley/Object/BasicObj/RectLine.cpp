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
	Vector2 halfSize = _size * 0.5f;

	v.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
	_vertices.push_back(v);

	v.pos = { halfSize.x, halfSize.y, 0.0f }; // ������ ��
	_vertices.push_back(v);

	v.pos = { halfSize.x, -halfSize.y, 0.0f }; // ������ �Ʒ�
	_vertices.push_back(v);

	v.pos = { -halfSize.x, -halfSize.y, 0.0f }; // ���� �Ʒ�
	_vertices.push_back(v);

	v.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
	_vertices.push_back(v);
}