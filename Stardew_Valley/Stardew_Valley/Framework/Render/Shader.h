#pragma once
class Shader
{
public:
	Shader(wstring path):_path(path) {}
	virtual ~Shader() {}

protected:
	virtual void CreateBlob(wstring path) abstract;
	virtual void CreateShader() abstract;
	virtual void SetShader() abstract;
	wstring _path;
	ComPtr<ID3DBlob> _blob;

};

