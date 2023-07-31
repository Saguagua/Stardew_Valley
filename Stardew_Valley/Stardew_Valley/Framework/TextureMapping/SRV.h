#pragma once
class SRV
{
public:
	SRV(wstring path);
	SRV(wstring path, Vector2 size);
	~SRV() {}

	void SetSRV(UINT slot = 0);

	Vector2 GetImageSize() { return _imgSize; }

private:
	Vector2 _imgSize;
	ComPtr<ID3D11ShaderResourceView> _srv;
};

