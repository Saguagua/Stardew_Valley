#pragma once
class VertexShader :public Shader
{
public:
	VertexShader(wstring path);
	virtual ~VertexShader() {}

	void SetIA_InputLayout();
	virtual void SetShader() override;

private:
	virtual void CreateBlob(wstring path) override;
	virtual void CreateShader() override;
	void CreateInputLayout(wstring path);

	ComPtr<ID3D11VertexShader> _vs;
	ComPtr<ID3D11InputLayout> _inputLayout;
};

