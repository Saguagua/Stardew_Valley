#pragma once
class TextureButton :public Button
{
public:
	TextureButton(wstring path, Vector2 size, CallBack callback);
	virtual ~TextureButton() {}

	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Update() override;

private:
	shared_ptr<TextureRect> _renderer;
};

