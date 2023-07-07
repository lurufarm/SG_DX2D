#include "SCENE_SelectScene.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
		 
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"

#include "Img_CatPattern.h"
#include "UI_Select.h"
#include "UI_Exit.h"


namespace sg
{
	SelectScene::SelectScene()
	{
		SetName(L"SelectScene");
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		float BgColor[3] = { 0.13f, 0.37f, 0.59f };
		GetDevice()->SetBgColor(BgColor);
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		UI_Select* story = object::Instantiate<UI_Select>(true, eLayerType::UI);
		UI_Select* party = object::Instantiate<UI_Select>(false, eLayerType::UI);
		UI_Exit* exit = object::Instantiate<UI_Exit>(eLayerType::UI);

		Img_CatPattern* pattern = object::Instantiate<Img_CatPattern>(eLayerType::BGImg);

		mFocus = object::Instantiate<UI_FocusBoxes>(eLayerType::UI);
		mFocus->AddSelectObj(exit);
		mFocus->AddSelectObj(story);
		mFocus->AddSelectObj(party);
		mFocus->SetSelectObj(story);

		GameObject* SelectSceneMaincamera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg);
		SelectSceneMaincamera->SetName(L"SelectSceneMaincamera");
		Camera* MaincameraComp = SelectSceneMaincamera->AddComp<Camera>();

		GameObject* SelectSceneUIcamera = object::Instantiate<GameObject>(Vector3(cameraPos.x, cameraPos.y, -20.0f), eLayerType::UI);
		SelectSceneUIcamera->SetName(L"SelectSceneUIcamera");
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
