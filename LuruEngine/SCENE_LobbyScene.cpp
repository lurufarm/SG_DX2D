#include "SCENE_LobbyScene.h"
#include "..\Engine_SOURCE\sgApplication.h"
#include "..\Engine_SOURCE\sgGraphicDevice_Dx11.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"
#include "SCRIPT_GridScript.h"

#include "Gobj_Grid.h"

#include "Img_Space1.h"
#include "Img_Space2.h"
#include "Img_LobbyMap.h"
#include "Img_LobbyMolding.h"

#include "Interact_LobbyCharacter.h"
#include "Interact_LobbyUpgrade.h"



namespace sg
{
	LobbyScene::LobbyScene()
	{
		SetName(L"LobbyScene");
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		float BgColor[3] = { 0.0f, 0.0f, 0.0f };
		graphics::GetDevice()->SetBgColor(BgColor);
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		object::Instantiate<Img_Space1>(eLayerType::BGImg);
		object::Instantiate<Img_Space2>(eLayerType::BGImg);
		object::Instantiate<Img_LobbyMap>(eLayerType::BGImg);
		object::Instantiate<Img_LobbyMolding>(Vector3(-1.1f, 0.85f, 0.0f), eLayerType::BGImg);
		object::Instantiate<Img_LobbyMolding>(Vector3(1.1f, 0.85f, 0.0f), eLayerType::BGImg);

		object::Instantiate<Interact_LobbyCharacter>(Vector3(-0.55, 0.1f, -0.1f), eLayerType::InteractableObject);
		object::Instantiate<Interact_LobbyUpgrade>(Vector3(0.55, 0.1f, -0.1f), eLayerType::InteractableObject);


		GameObject* LobbyScenecamera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg);
		Camera* cameraComp = LobbyScenecamera->AddComp<Camera>();

		
		Gobj_Grid* grid = object::Instantiate<Gobj_Grid>(eLayerType::Grid);
		SCRIPT_GridScript* mSC_Grid = grid->AddComp<SCRIPT_GridScript>();
		mSC_Grid->SetCamera(cameraComp);

	}
	void LobbyScene::Update()
	{
		Scene::Update();
	}
	void LobbyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void LobbyScene::Render()
	{
		Scene::Render();
	}
	void LobbyScene::OnEnter()
	{
		LobbyScene::Initialize();
	}
	void LobbyScene::OnExit()
	{
	}
}