#include "framework.h"
#include "DayFinishScene.h"

DayFinishScene::DayFinishScene()
{
	_backGroundSlot = make_shared<Transform>();
	_panelSlot = make_shared<Transform>();

	_panelSlot->SetPos(Vector2(0, 280));
	_datePos = (Vector2(560, 70));


	_textPanel = make_shared<Sprite>("TextBox", Vector2(500, 100), SpriteType::UI);
	_backGround = make_shared<Sprite>("Cloudy_Ocean_BG_Night", Vector2(WIN_WIDTH, WIN_HEIGHT), SpriteType::UI);
	_okayBtn = make_shared<TextureButton>("OkayButton", Vector2(50, 50));

	_okayBtn->SetPos(Vector2(450, -250));

	CallBack cb = std::bind(&DayFinishScene::SceneChange, this);

	_okayBtn->AddPushEvent(cb);

	_cb = std::bind(&DayFinishScene::WhenCoverDark, this);

	shared_ptr<CalculateUI> ui1 = make_shared<CalculateUI>(L"³ó»ç", Vector2(500, 100));
	ui1->SetPos(Vector2(0, 150));
	_calculates.push_back(ui1);
	shared_ptr<CalculateUI> ui2 = make_shared<CalculateUI>(L"³¬½Ã", Vector2(500, 100));
	ui2->SetPos(Vector2(0, 50));
	_calculates.push_back(ui2);
	shared_ptr<CalculateUI> ui3 = make_shared<CalculateUI>(L"Ã¤±¤", Vector2(500, 100));
	ui3->SetPos(Vector2(0, -50));
	_calculates.push_back(ui3);
	shared_ptr<CalculateUI> ui4 = make_shared<CalculateUI>(L"±âÅ¸", Vector2(500, 100));
	ui4->SetPos(Vector2(0, -150));
	_calculates.push_back(ui4);
	shared_ptr<CalculateUI> ui5 = make_shared<CalculateUI>(L"ÃÑÇÕ", Vector2(500, 100));
	ui5->SetPos(Vector2(0, -250));
	_calculates.push_back(ui5);
}

void DayFinishScene::Update()
{
	_backGroundSlot->Update();
	_panelSlot->Update();

	for (size_t i = 0; i < _calculates.size(); i++)
	{
		_calculates[i]->Update();
	}

	_okayBtn->Update();
}

void DayFinishScene::Render()
{
}

void DayFinishScene::Initialize()
{
	LightManager::GetInstance()->_mapToolMode = false;
	MONEYMANAGER->Update();

	_calculates[0]->SetPrice(MONEYMANAGER->_farmmingPrice);
	_calculates[1]->SetPrice(MONEYMANAGER->_fishingPrice);
	_calculates[2]->SetPrice(MONEYMANAGER->_miningPrice);
	_calculates[3]->SetPrice(MONEYMANAGER->_extraPrice);
	_calculates[4]->SetPrice(MONEYMANAGER->_priceSum);

	_month = to_wstring(TIMER->GetMonth());
	_day = to_wstring(TIMER->GetDay());
}

void DayFinishScene::WhenCoverDark()
{
	TIMER->SetNextDay();
	DATA->PlaySave();
	SCENEMANAGER->ChangeScene(SceneManager::TEST);
}

void DayFinishScene::PostRender()
{
	
	if (!SCENEMANAGER->_cover->IsActive())
	{
		_backGroundSlot->Set_World();
		_backGround->Render();

		_panelSlot->Set_World();
		_textPanel->Render();

		Font::GetInstance()->RenderText(_month + L"¿ù " + _day + L"ÀÏ", "Nanum", _datePos);

		for (size_t i = 0; i < _calculates.size(); i++)
		{
			_calculates[i]->PostRender();
		}

		_okayBtn->Render();
	}
}

void DayFinishScene::SceneChange()
{
	SCENEMANAGER->_cover->FadeStart(_cb, nullptr);
}
