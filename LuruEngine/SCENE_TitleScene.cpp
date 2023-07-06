#include "SCENE_TitleScene.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
		 
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"

#include "Img_TitleImg01.h"
#include "Img_Logo.h"

#include "UI_Select.h"
#include "UI_FocusBox.h"

namespace sg
{
	TitleScene::TitleScene()
	{
		SetName(L"TitleScene");
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		float BgColor[3] = { 0.0f, 0.0f, 0.0f };
		GetDevice()->SetBgColor(BgColor);

		Img_Title* title01 = new Img_Title();
		AddGameObj(eLayerType::BGImg, title01);

		Img_Logo* logo01 = new Img_Logo();
		AddGameObj(eLayerType::BGImg, logo01);
		
		GameObject* camera = new GameObject();
		AddGameObj(eLayerType::BGImg, camera);
		camera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComp<Camera>();
		//camera->AddComp<CameraScript>();

		GameObject* UIcamera = new GameObject();
		AddGameObj(eLayerType::UI, UIcamera);
		UIcamera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* UIcameraComp = UIcamera->AddComp<Camera>();
	}
	void TitleScene::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"SelectScene");
		}

		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}