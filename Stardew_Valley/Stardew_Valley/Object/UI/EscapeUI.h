#pragma once
class SceneManager;

class EscapeUI
{
public:
	EscapeUI(SceneManager* instance);
	~EscapeUI() {}


	void Update();
	void PostRender();

	void SetActive(bool val) { _isActive = val; }
	void SwitchActive() { _isActive = !_isActive; }

private:
	void PressOkay();
	void PressCancel();

	CallBackInt _cb;

	bool _isActive = false;

	shared_ptr<Sprite> _renderer;
	shared_ptr<TextureButton> _okBtn;
	shared_ptr<TextureButton> _cancelBtn;

	shared_ptr<Transform> _bodySlot;
};

