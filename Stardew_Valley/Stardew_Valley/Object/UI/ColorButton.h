#pragma once
class ColorButton :public Button
{
public:
	ColorButton(XMFLOAT4 color, Vector2 size);
	~ColorButton() {}

	virtual void Render() override;
	virtual void Update() override;

private:
	shared_ptr<SingleColorRect> _renderer;
};

