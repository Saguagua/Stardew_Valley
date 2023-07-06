#pragma once
class TextureButton :public Button
{
public:
	TextureButton(wstring path, Vector2 size);
	TextureButton(wstring path, Vector2 clip, Vector2 size);
	virtual ~TextureButton() {}

	virtual void Render() override;
	virtual void Update() override;

	void SetFrame(Vector2 frame) { _curFrame = frame; }
private:
	weak_ptr<TextureRect> _renderer;
	Vector2 _curFrame;
};

