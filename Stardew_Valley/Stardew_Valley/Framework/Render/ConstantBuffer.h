#pragma once

class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer() {}

	void Update();
	void Set_PS(UINT slot = 0);
	void Set_VS(UINT slot = 0);
private:
	void CreateBuffer();

	ComPtr<ID3D11Buffer> _buffer;

	void* _data;
	UINT _dataSize;
};

