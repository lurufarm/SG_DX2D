#include "SCENE_TitleScene.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
		 
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"

#include "Img_TitleImg01.h"
#include "Img_Logo.h"

#include "UI_Select.h"
#include "UI_FocusBox.h"

#include "..\Engine_SOURCE\sgParticleSystem.h"
#include "..\Engine_SOURCE\sgFontWrapper.h"

namespace sg
{
	TitleScene::TitleScene()
	{
		SetName(L"00_TitleScene");
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{

		float BgColor[3] = { 0.0f, 0.0f, 0.0f };
		GetDevice()->SetBgColor(BgColor);
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		object::Instantiate<Img_Title>(eLayerType::BGImg, this);
		object::Instantiate<Img_Logo>(eLayerType::BGImg, this);

		GameObject* camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		Camera* cameraComp = camera->AddComp<Camera>();

		GameObject* light = new GameObject();
		AddGameObj(eLayerType::Light, light);
		Light* lightcomp = light->AddComp<Light>();
		Vector4 lightcolor = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
		lightcomp->SetType(eLightType::Directional);
		lightcomp->SetColor(lightcolor);
		
		//wcscpy_s(FontWrapper::mText, L"Test");
		//FontWrapper::SetFontOption(10, 20, 20.0f, FONT_RGBA(255, 0, 255, 255));


	}
	void TitleScene::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			SceneManager::LoadNextScene();
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