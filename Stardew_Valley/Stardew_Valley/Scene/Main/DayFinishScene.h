#pragma once
class DayFinishScene :public Scene
{
public:
	DayFinishScene();
	~DayFinishScene() {}

	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void WhenCoverDark() override;
	virtual void PostRender() override;
	void SceneChange();
private:
	shared_ptr<Transform> _backGroundSlot;
	shared_ptr<Transform> _panelSlot;
	Vector2 _datePos;

	wstring _month;
	wstring _day;

	shared_ptr<Sprite> _backGround;
	shared_ptr<TextureButton> _okayBtn;
	shared_ptr<Sprite> _textPanel;
	
	vector<shared_ptr<CalculateUI>> _calculates;

	CallBack _cb;
};

