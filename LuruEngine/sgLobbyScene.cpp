#include "sgLobbyScene.h"
#include "sgSceneManager.h"
#include "sgInput.h"
#include "sgTime.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgApplication.h"

#include "sgTransform.h"
#include "sgCamera.h"

#include "sgCameraScript.h"

#include "Img_Space1.h"
#include "Img_Space2.h"
#include "Img_LobbyMap.h"

namespace sg
{
	LobbyScene::LobbyScene()
	{
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

		GameObject* LobbyScenecamera = new GameObject();
		AddGameObj(eLayerType::BGImg, LobbyScenecamera);
		LobbyScenecamera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = LobbyScenecamera->AddComp<Camera>();

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