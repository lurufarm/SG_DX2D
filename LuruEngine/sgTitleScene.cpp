#include "sgTitleScene.h"
#include "sgSceneManager.h"
#include "sgInput.h"
#include "sgTime.h"
		 
#include "sgTransform.h"
#include "sgCamera.h"

#include "sgCameraScript.h"

#include "Img_TitleImg01.h"
#include "Img_Logo.h"
#include "UI_Select.h"

#include "UI_FocusBox.h"

namespace sg
{
	TitleScene::TitleScene()
	{
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

		//logo01->GetComp<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.0f));

		//UI_FocusBox* test = new UI_FocusBox(0);
		//AddGameObj(eLayerType::UI, test);

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