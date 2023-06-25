#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer() {}

	void SetIA_IndexBuffer(UINT slot = 0);

private:
	void CreateIndexBuffer(void* data);

	ComPtr<ID3D11Buffer> _buffer;
	UINT _count;
};

