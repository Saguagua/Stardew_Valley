#pragma once
#include "framework.h"

struct MatrixBuffer :public ConstantBuffer
{
	MatrixBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity();
	}

	virtual ~MatrixBuffer() {}

	void SetMatrix(XMMATRIX matrix)
	{
		matrix = XMMatrixTranspose(matrix);
		_data.matrix = matrix;
	}

	XMMATRIX GetMatrix()
	{
		return _data.matrix;
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	};

	Data _data;
};

struct ColorBuffer :public ConstantBuffer
{
	ColorBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{
		_data.color = XMFLOAT4();
	}

	virtual ~ColorBuffer() {}

	void SetColor(XMFLOAT4 color)
	{
		_data.color = color;
		Update();
	}

	XMFLOAT4 GetColor()
	{
		return _data.color;
	}

private:
	struct Data
	{
		XMFLOAT4 color;
	};

	Data _data;
};

struct TileInfoBuffer : public ConstantBuffer
{
	TileInfoBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{}

	virtual ~TileInfoBuffer() {}

	void SetMaxFrame(Vector2 max) { _data.maxFrame = max; }
	void SetStart(Vector2 start) { _data.startPos = start; }

	Vector2& GetMaxFrame() { return _data.maxFrame; }
	Vector2& GetStart() { return _data.startPos; }

private:
	struct Data
	{
		Vector2 maxFrame = {0,0};
		Vector2 startPos = {0,0};
	};

	Data _data;
};