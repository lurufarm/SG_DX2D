#include "SCENE_SelectScene.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
		 
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCENE_TitleScene.h"

#include "SCRIPT_CameraScript.h"

#include "Img_CatPattern.h"
#include "Img_SelectText.h"

#include "UI_Select.h"
#include "UI_Exit.h"

#include "Gobj_Sound.h"


namespace sg
{
	SelectScene::SelectScene()
	{
		SetName(L"01_SelectScene");
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		UI_Select* story = object::Instantiate<UI_Select>(true, eLayerType::UI, this);
		UI_Select* party = object::Instantiate<UI_Select>(false, eLayerType::UI, this);
		Img_SelectText* story_text = object::Instantiate<Img_SelectText>(true, eLayerType::UI, this);
		Img_SelectText* party_text = object::Instantiate<Img_SelectText>(false, eLayerType::UI, this);
		UI_Exit* exit = object::Instantiate<UI_Exit>(eLayerType::UI, this);

		Img_CatPattern* pattern = object::Instantiate<Img_CatPattern>(eLayerType::BGImg, this);

		mFocus = object::Instantiate<UI_FocusBoxes>(this, eLayerType::UI, this);
		mFocus->AddSelectObj(exit);
		mFocus->AddSelectObj(story);
		mFocus->AddSelectObj(party);
		mFocus->SetSelectObj(story);

		GameObject* SelectSceneMaincamera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		SelectSceneMaincamera->SetName(L"SelectSceneMaincamera");
		Camera* MaincameraComp = SelectSceneMaincamera->AddComp<Camera>();
		MaincameraComp->TurnLayerMask(eLayerType::UI, false);

		GameObject* SelectSceneUIcamera = object::Instantiate<GameObject>(Vector3(cameraPos.x, cameraPos.y, -20.0f), eLayerType::UI, this);
		SelectSceneUIcamera->SetName(L"SelectSceneUIcamera");
		Camera* UIcameraComp = SelectSceneUIcamera->AddComp<Camera>();
		UIcameraComp->DisableLayerMask();
		UIcameraComp->TurnLayerMask(eLayerType::UI, true);

		GameObject* light = new GameObject();
		AddGameObj(eLayerType::Light, light);
		Light* lightcomp = light->AddComp<Light>();
		Vector4 lightcolor = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
		lightcomp->SetType(eLightType::Directional);
		lightcomp->SetColor(lightcolor);


	}
	void SelectScene::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			SceneManager::LoadNextScene();
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
		float BgColor[3] = { 0.13f, 0.37f, 0.59f };
		GetDevice()->SetBgColor(BgColor);
	}
	void SelectScene::OnExit()
	{
		Scene* sc = SceneManager::FindScene(L"00_TitleScene");
		Gobj_Sound* bgm = dynamic_cast<TitleScene*>(sc)->GetTItleBGM();
		bgm->Stop();
	}
}
