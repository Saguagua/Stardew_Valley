#pragma once
class Window
{
public:
	Window(Vector2 size, XMFLOAT4 color = GRAY);
	~Window() {}

	void Render();
	void PostRender();
	void Update();

	void AddButton(shared_ptr<Button> button);
	void AddWindow(shared_ptr<Window> other);

	void KeyInput();

	void SetColor(XMFLOAT4 color) { _renderer->SetColor(color); }
	void SetScale(Vector2 scale) { _col->SetScale(scale); }
	void SetPos(Vector2 pos) { _col->SetPos(pos); }
	void SetRotate(float angle) { _col->SetAngle(angle); }

	shared_ptr<RectCollider> GetCollider() { return _col; }
private:
	shared_ptr<RectCollider> _col;
	shared_ptr<SingleColorRect> _renderer;
	Vector2 _size;

	Vector2 _centerToMouse;

	vector<weak_ptr<Window>> _windows;
	vector<weak_ptr<Button>> _buttons;
};

