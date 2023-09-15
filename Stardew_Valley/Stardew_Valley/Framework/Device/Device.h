#pragma once
class Device
{
private:
	Device();
	~Device() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Device();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Device* GetInstance()
	{
		assert(_instance != nullptr);

		return _instance;
	}

	ComPtr<ID3D11Device> GetDevice()
	{
		return _device;
	}

	ComPtr<ID3D11DeviceContext> GetContext()
	{
		return _deviceContext;
	}

	ComPtr<IDXGISwapChain> GetSwapChain()
	{
		return _swapChain;
	}

	void Clear();

	void Present();

	Vector2 GetClientSize() { return clientSize; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTarget();

	static Device* _instance;

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<IDXGISwapChain> _swapChain;
	ComPtr<ID3D11RenderTargetView> _renderTarget;

	Vector2 clientSize;
};

