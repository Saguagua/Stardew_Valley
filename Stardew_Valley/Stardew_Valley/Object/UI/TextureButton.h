#pragma once
class TextureButton :public Button
{
public:
	TextureButton(string name, Vector2 size);
	~TextureButton() {}

	void SetPos(Vector2 pos);

	virtual void Render() override;
	void PostRender();
	virtual void Update() override;

	string GetName();
	void SetName(string name);

	void SetFont(wstring word);
	void SetFontPos(Vector2 pos);

private:
	shared_ptr<Sprite> _renderer;
	wstring _font = L"";
	Vector2 _fontPos;
	Vector2 _fontWorld;
};

