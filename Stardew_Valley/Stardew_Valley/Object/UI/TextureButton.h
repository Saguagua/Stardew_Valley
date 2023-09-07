#pragma once
class TextureButton :public Button
{
public:
	TextureButton(string name, Vector2 size);
	~TextureButton() {}

	virtual void Render() override;
	void PostRender();
	virtual void Update() override;

	string GetName();
	void SetName(string name);

private:
	shared_ptr<Sprite> _renderer;
};

