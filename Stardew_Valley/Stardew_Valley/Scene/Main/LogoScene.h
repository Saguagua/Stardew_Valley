#pragma once
class LogoScene :public Scene
{

public:
	LogoScene();
	~LogoScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void PostRender() override;
private:
	void SceneChange(int index);
	virtual void WhenCoverDark() override;
	
	shared_ptr<Transform> _backGroundSlot;
	shared_ptr<Transform> _logoSlot;

	shared_ptr<Sprite> _backGround;
	shared_ptr<Sprite> _logo;
	shared_ptr<TextureButton> _mapToolBtn;
	shared_ptr<TextureButton> _playBtn;
	shared_ptr<TextureButton> _exitBtn;

	int _nextSceneIndex;
	CallBack _cb;
};

