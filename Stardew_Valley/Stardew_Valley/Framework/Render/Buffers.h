#pragma once
#include "framework.h"

struct MatrixBuffer :public ConstantBuffer
{
	MatrixBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity();
	}

	~MatrixBuffer() {}

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
		_data.ratio = Vector2(1, 1);
	}

	~ColorBuffer() {}

	void SetColor(XMFLOAT4 color)
	{
		_data.color = color;
	}
	void SetRatio(Vector2 ratio)
	{
		_data.ratio = ratio;
	}
	void AddColor(XMFLOAT4 color)
	{
		_data.color.x += color.x;
		if (_data.color.x > 1) _data.color.x = 1;
		else if (_data.color.x < 0) _data.color.x = 0;

		_data.color.y += color.y;
		if (_data.color.y > 1) _data.color.y = 1;
		else if (_data.color.y < 0) _data.color.y = 0;

		_data.color.z += color.z;
		if (_data.color.z > 1) _data.color.z = 1;
		else if (_data.color.z < 0) _data.color.z = 0;
	}

	XMFLOAT4 GetColor()
	{
		return _data.color;
	}

	Vector2 GetRatio()
	{
		return _data.ratio;
	}

private:
	struct Data
	{
		XMFLOAT4 color;
		Vector2 ratio;
		int padding[2];
	};

	Data _data;
};

struct FrameBuffer : public ConstantBuffer
{
	FrameBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{}

	~FrameBuffer() {}

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

struct XMLBuffer : public ConstantBuffer
{
	XMLBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{}

	~XMLBuffer() {}

	void SetSize(Vector2 size) { _data.size = size; }
	void SetStart(Vector2 start) { _data.startPos = start; }
	void SetImgSize(Vector2 size) { _data.imgSize = size; }
	void SetRatio(Vector2 ratio) { _data.ratio = ratio; }

	Vector2& GetSize() { return _data.size; }
	Vector2& GetStart() { return _data.startPos; }
	Vector2& GetImgSize() { return _data.imgSize; }
	Vector2& GetRatio() { return _data.ratio; }

private:
	struct Data
	{
		Vector2 startPos;
		Vector2 size;
		Vector2 imgSize;
		Vector2 ratio = {1,1};
	};

	Data _data;
};

struct LightPosBuffer : public ConstantBuffer
{
	LightPosBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{
		for (int i = 0; i < 29; i++)
			_data.poses[i] = { -1,-1,-1,-1 };
	}

	~LightPosBuffer() {}

	XMFLOAT4* GetPoses()
	{
		return _data.poses;
	}

private:
	struct Data
	{
		XMFLOAT4 poses[29];
	};

	Data _data;
};

struct LightColorBuffer : public ConstantBuffer
{
	LightColorBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{
		for (int i = 0; i < 30; i++)
			_data.colors[i] = { 0,0,0,1 };
	}

	~LightColorBuffer() {}

	XMFLOAT4* GetColors()
	{
		return _data.colors;
	}

	XMFLOAT4& GetSun()
	{
		return _data.colors[0];
	}

	void GetDarker(XMFLOAT4 val)
	{
		_data.colors[0].x -= val.x;
		if (_data.colors[0].x < 0.1)
			_data.colors[0].x = 0.1;

		_data.colors[0].y -= val.y;
		if (_data.colors[0].y < 0.1)
			_data.colors[0].y = 0.1;

		_data.colors[0].z -= val.z;
		if (_data.colors[0].z < 0.1)
			_data.colors[0].z = 0.1;
	}

	void GetBrighter(XMFLOAT4 val)
	{
		_data.colors[0].x += val.x;
		if (_data.colors[0].x > 1.2)
			_data.colors[0].x = 1.2;

		_data.colors[0].y += val.y;
		if (_data.colors[0].y > 1.2)
			_data.colors[0].y = 1.2;

		_data.colors[0].z += val.z;
		if (_data.colors[0].z > 1.2)
			_data.colors[0].z = 1.2;
	}
private:
	struct Data
	{
		XMFLOAT4 colors[30];
	};

	Data _data;
};


struct EffectBuffer : public ConstantBuffer
{
	EffectBuffer():ConstantBuffer(&_data, sizeof(_data)) {}

	void ReverseAlpha() 
	{ 
		if (_data.alphaZero) _data.alphaZero = 0;
		else _data.alphaZero = 1;
	}

	struct Data
	{
		int alphaZero = 0;
		int padding[3] = {0,0,0};
	};

	Data _data;
};