#pragma once
struct Vector2 : public XMFLOAT2
{
	Vector2(): XMFLOAT2(0.0f, 0.0f) {}
	Vector2(float x, float y) :XMFLOAT2(x, y) {}
	Vector2(int x, int y) :XMFLOAT2(x, y) {}
	~Vector2() {}

	Vector2 operator+(const Vector2& other) const
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;

		return result;
	}

	Vector2 operator-(const Vector2& other) const
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;

		return result;
	}

	Vector2 operator*(float scalar) const
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

	Vector2 TransformCoord(XMMATRIX matrix)
	{
		XMVECTOR tmp = XMLoadFloat2(this);

		tmp = XMVector2TransformCoord(tmp, matrix);
		Vector2 result;
		XMStoreFloat2(&result, tmp);

		return result;
	}
};

