#include "SCENE_LobbyScene.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgGraphicDevice_Dx11.h"
#include "..\Engine_SOURCE\sgApplication.h"

#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"
#include "SCRIPT_GridScript.h"

#include "Img_Space1.h"
#include "Img_Space2.h"
#include "Img_LobbyMap.h"
#include "Img_LobbyMolding.h"

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

		Img_Space1* space1 = new Img_Space1();
		AddGameObj(eLayerType::BGImg, space1);

		Img_Space2* space2 = new Img_Space2();
		AddGameObj(eLayerType::BGImg, space2);

		Img_LobbyMap* lobby = new Img_LobbyMap();
		AddGameObj(eLayerType::BGImg, lobby);

		Img_LobbyMolding* molding0 = new Img_LobbyMolding();
		AddGameObj(eLayerType::BGImg, molding0);
		molding0->GetComp<Transform>()->SetPosition(-1.1f, 0.85f, 0.0f);

		Img_LobbyMolding* molding1 = new Img_LobbyMolding();
		AddGameObj(eLayerType::BGImg, molding1);
		molding1->GetComp<Transform>()->SetPosition(1.1f, 0.85f, 0.0f);

		Interact_LobbyUpgrade* upgradetotem = new Interact_LobbyUpgrade();
		AddGameObj(eLayerType::BGImg, upgradetotem);

		GameObject* LobbyScenecamera = new GameObject();
		AddGameObj(eLayerType::BGImg, LobbyScenecamera);
		LobbyScenecamera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = LobbyScenecamera->AddComp<Camera>();

		GameObject* grid = new GameObject();
		grid->SetName(L"Grid");
		AddGameObj(eLayerType::Grid, grid);
		MeshRenderer* mr = grid->AddComp<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		SCRIPT_GridScript* script_grid = grid->AddComp<SCRIPT_GridScript>();
		script_grid->SetCamera(cameraComp);


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