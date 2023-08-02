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
		_data.ratio = Vector2(1, 1);
	}

	virtual ~ColorBuffer() {}

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
		_data.color.y += color.y;
		_data.color.z += color.z;
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

	virtual ~FrameBuffer() {}

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

	virtual ~XMLBuffer() {}

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

struct LightPoseBuffer : public ConstantBuffer
{
	LightPoseBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{
		_data.lightPose1 = {0,0,0,1};
		_data.lightPose2 = {0,0,0,1};
		_data.lightPose3 = {0,0,0,1};
		_data.lightPose4 = {0,0,0,1};
	}

	virtual ~LightPoseBuffer() {}

	void SetFirstLight(XMFLOAT4 light) { _data.lightPose1 = light; }
	void SetSecondLight(XMFLOAT4 light) { _data.lightPose2 = light; }
	void SetThirdLight(XMFLOAT4 light) { _data.lightPose3 = light; }
	void SetFourthLight(XMFLOAT4 light) { _data.lightPose4 = light; }

	XMFLOAT4 GetFirstLight() { return _data.lightPose1; }
	XMFLOAT4 GetSecondLight() { return _data.lightPose2; }
	XMFLOAT4 GetThirdLight() { return _data.lightPose3; }
	XMFLOAT4 GetFourthLight() { return _data.lightPose4; }

private:
	struct Data
	{
		XMFLOAT4 lightPose1;
		XMFLOAT4 lightPose2;
		XMFLOAT4 lightPose3;
		XMFLOAT4 lightPose4;
	};

	Data _data;
};

struct LightColorBuffer : public ConstantBuffer
{
	LightColorBuffer() :ConstantBuffer(&_data, sizeof(_data))
	{
		_data.lightColor1 = {0,0,0,1};
		_data.lightColor2 = {0,0,0,1};
		_data.lightColor3 = {0,0,0,1};
		_data.lightColor4 = {0,0,0,1};
	}

	virtual ~LightColorBuffer() {}

	void SetFirstLight(XMFLOAT4 light) { _data.lightColor1 = light; }
	void SetSecondLight(XMFLOAT4 light) { _data.lightColor2 = light; }
	void SetThirdLight(XMFLOAT4 light) { _data.lightColor3 = light; }
	void SetFourthLight(XMFLOAT4 light) { _data.lightColor4 = light; }

	XMFLOAT4 GetFirstLight() { return _data.lightColor1; }
	XMFLOAT4 GetSecondLight() { return _data.lightColor2; }
	XMFLOAT4 GetThirdLight() { return _data.lightColor3; }
	XMFLOAT4 GetFourthLight() { return _data.lightColor4; }

private:
	struct Data
	{
		XMFLOAT4 lightColor1;
		XMFLOAT4 lightColor2;
		XMFLOAT4 lightColor3;
		XMFLOAT4 lightColor4;
	};

	Data _data;
};
