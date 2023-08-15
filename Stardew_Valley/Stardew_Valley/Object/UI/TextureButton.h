#pragma once
class TextureButton :public Button
{
public:
	TextureButton(wstring path, string name, Vector2 size);
	virtual ~TextureButton() {}

	virtual void Render() override;
	virtual void Update() override;

	string GetName();
	void SetName(string name);

private:
	shared_ptr<class Sprite> _renderer;
};

