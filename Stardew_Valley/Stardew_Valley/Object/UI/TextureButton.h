#pragma once
class TextureButton :public Button
{
public:
	TextureButton(wstring path, Vector2 size);
	TextureButton(wstring path, Vector2 frame, Vector2 size);
	virtual ~TextureButton() {}

	virtual void Render() override;
	virtual void Update() override;

	shared_ptr<TextureRect> GetTexture() { return _renderer; }

	void SetFrame(Vector2 frame) { _curFrame = frame; }
	Vector2 GetCurFrame() { return _curFrame; }
	Vector2 GetMaxFrame() { return _renderer->GetMaxFrame(); }
private:
	shared_ptr<TextureRect> _renderer;
	Vector2 _curFrame = {0, 0};
};

