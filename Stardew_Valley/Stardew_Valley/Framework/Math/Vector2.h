#pragma once
struct Vector2
{
	Vector2():x(0), y(0) {}
	Vector2(float x, float y) :x(x), y(y) {}
	Vector2(int x, int y) :x(x), y(y) {}
	~Vector2() {}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;

		return result;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;

		return result;
	}

	Vector2 operator*(float scalar)
	{
		Vector2 result;
		result.x = x * scalar;
		result.y = y * scalar;

		return result;
	}

	Vector2& operator-()
	{
		x *= -1;
		y *= -1;

		return *this;
	}

	Vector2& operator+=(Vector2 other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	float Dot(const Vector2& other)
	{
		return x * other.x + y * other.y;
	}

	float Length()
	{
		return x * x + y * y;
	}

	float x;
	float y;
};

