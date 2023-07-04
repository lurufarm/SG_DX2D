#include "sgSelectScene.h"
#include "sgSceneManager.h"
#include "sgInput.h"
#include "sgTime.h"
		 
#include "sgTransform.h"
#include "sgCamera.h"

#include "sgCameraScript.h"

#include "Img_CatPattern.h"
#include "UI_Select.h"
#include "UI_Exit.h"


namespace sg
{
	SelectScene::SelectScene()
	{
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		float BgColor[3] = { 0.13f, 0.37f, 0.59f };
		GetDevice()->SetBgColor(BgColor);

		UI_Select* story = new UI_Select(true);
		AddGameObj(eLayerType::UI, story);
		//mSelectObj.push_back(story);

		mFocus = new UI_FocusBoxes();
		mFocus->SetSelectObj(story);
		AddGameObj(eLayerType::UI, mFocus);

		UI_Select* party = new UI_Select(false);
		AddGameObj(eLayerType::UI, party);

		UI_Exit* exit = new UI_Exit();
		AddGameObj(eLayerType::UI, exit);

		Img_CatPattern* catpattern0 = new Img_CatPattern();
		AddGameObj(eLayerType::BGImg, catpattern0);
		Transform* cptr0 = catpattern0->GetComp<Transform>();

		GameObject* SelectSceneMaincamera = new GameObject();
		AddGameObj(eLayerType::BGImg, SelectSceneMaincamera);
		SelectSceneMaincamera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* MaincameraComp = SelectSceneMaincamera->AddComp<Camera>();

		GameObject* SelectSceneUIcamera = new GameObject();
		AddGameObj(eLayerType::UI, SelectSceneUIcamera);
		SelectSceneUIcamera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -20.0f));
		Camera* UIcameraComp = SelectSceneUIcamera->AddComp<Camera>();
	}
	void SelectScene::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"LobbyScene");
		}
		Scene::Update();
	}
	void SelectScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void SelectScene::Render()
	{
		Scene::Render();
	}
	void SelectScene::OnEnter()
	{
		SelectScene::Initialize();
	}
	void SelectScene::OnExit()
	{

	}
}
