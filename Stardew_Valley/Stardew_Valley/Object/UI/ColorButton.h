#pragma once
class ColorButton :public Button
{
public:
	ColorButton(XMFLOAT4 color, Vector2 size, CallBack callback = nullptr);
	virtual ~ColorButton() {}

	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Update() override;
	
private:
	shared_ptr<SingleColorRect> _renderer;
};

