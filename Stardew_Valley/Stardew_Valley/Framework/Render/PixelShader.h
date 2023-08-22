#pragma once
class PixelShader :public Shader
{
public:
	PixelShader(wstring path);
	~PixelShader() {}

	virtual void SetShader() override;
	
private:
	virtual void CreateBlob(wstring path) override;
	virtual void CreateShader() override;

	ComPtr<ID3D11PixelShader> _ps;
};

