#include "framework.h"
#include "EscapeUI.h"

EscapeUI::EscapeUI(SceneManager* instance)
{
	_bodySlot = make_shared<Transform>();
	_renderer = make_shared < Sprite >("TextBox", Vector2(400, 300), SpriteType::UI);
	_okBtn = make_shared<TextureButton>("OkayButton", Vector2(70, 50));
	_cancelBtn = make_shared<TextureButton>("CancelButton", Vector2(70, 50));

	_okBtn->GetCollider()->SetParent(_bodySlot);
	_cancelBtn->GetCollider()->SetParent(_bodySlot);
	_okBtn->SetPos(Vector2(-100,-30));
	_cancelBtn->SetPos(Vector2(100, -30));

	_cb = std::bind(&SceneManager::ChangeScene, instance, SceneManager::SceneIndex::LOGO);

	CallBack OkCB = std::bind(&EscapeUI::PressOkay, this);
	CallBack CancelCB = std::bind(&EscapeUI::PressCancel, this);

	_okBtn->AddPushEvent(OkCB);
	_cancelBtn->AddPushEvent(CancelCB);
}

void EscapeUI::Update()
{
	if (!_isActive)
		return;

	_bodySlot->Update();
	_okBtn->Update();
	_cancelBtn->Update();
}

void EscapeUI::PostRender()
{
	if (!_isActive)
		return;

	_bodySlot->Update();
	_renderer->Render();

	Font::GetInstance()->RenderText(L"메인으로 돌아가기", "Nanum", Vector2(550, 300));

	_okBtn->PostRender();
	_cancelBtn->PostRender();
}

void EscapeUI::PressOkay()
{
	SCENEMANAGER->_cover->FadeStart(nullptr, _cb);
	_isActive = false;
}

void EscapeUI::PressCancel()
{
	_isActive = false;
}
