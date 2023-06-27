#pragma once
Vector2 Lerp(Vector2 start, Vector2 end, float speed)
{
	return start + (end - start) * speed;
}