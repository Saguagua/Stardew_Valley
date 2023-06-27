#include "framework.h"
#include "CircleLine.h"

CircleLine::CircleLine(float radius)
:_radius(radius)
{
	CreateVertices();
	CreateData();

	_cBuffer->SetColor(_color);
	_cBuffer->Update();
}

void CircleLine::CreateVertices()
{
	Vertex v;

	for (int i = 0; i < 37; i++)
	{
		v.pos = { _radius * cosf(i * PI / 18.0f), _radius * sinf(i * PI / 18.0f), 0.0f };
		_vertices.push_back(v);
	}
}
