#include "SCENE_LobbyScene.h"
#include "..\Engine_SOURCE\sgApplication.h"
#include "..\Engine_SOURCE\sgGraphicDevice_Dx11.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "..\Engine_SOURCE\sgCollider2D.h"

#include "SCRIPT_CameraScript.h"
#include "SCRIPT_GridScript.h"

#include "Img_Space1.h"
#include "Img_Space2.h"
#include "Img_LobbyMap.h"
#include "Img_LobbyMolding.h"

#include "UI_Icons.h"
#include "UI_FocusBoxes.h"
#include "UI_FocusBoxes2.h"

#include "Interact_LobbyCharacter.h"
#include "Interact_LobbyUpgrade.h"
#include "Interact_LobbyCardBook.h"
#include "Interact_LobbyGate.h"

#include "Gobj_Player.h"
#include "Char_Cheese.h"

#include "Tile_TilePalette.h"

#include "SCRIPT_MainCamera.h"
#include "SCRIPT_UICamera.h"

extern sg::Gobj_Player* Player;

namespace sg
{

	LobbyScene::LobbyScene()
		: mFocus(nullptr)
	{
		SetName(L"LobbyScene");
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		Player = object::Instantiate<Gobj_Player>(Vector3(0.0f, 0.0f, -2.0f),eLayerType::Player, this);
		Player->Initialize();
		

		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		object::Instantiate<Img_Space1>(eLayerType::BGImg, this);
		object::Instantiate<Img_Space2>(eLayerType::BGImg, this);
		object::Instantiate<Img_LobbyMap>(eLayerType::BGImg, this);
		object::Instantiate<Img_LobbyMolding>(Vector3(-71.5, 55.25, 0.0f), eLayerType::Monster, this);
		object::Instantiate<Img_LobbyMolding>(Vector3(71.5, 55.25, 0.0f), eLayerType::BGImg, this);
		
		Interact_LobbyCharacter* character = object::Instantiate<Interact_LobbyCharacter>(Vector3(-35.75, 6.5f, -0.1f), eLayerType::InteractableObject, this);
		Interact_LobbyUpgrade* upgrade = object::Instantiate<Interact_LobbyUpgrade>(Vector3(35.75, 6.5f, -0.1f), eLayerType::InteractableObject, this);
		Interact_LobbyCardBook* cardbook = object::Instantiate<Interact_LobbyCardBook>(Vector3(35.75, -50.0f, -0.1f), eLayerType::InteractableObject, this);
		Interact_LobbyGate* gate = object::Instantiate<Interact_LobbyGate>(Vector3(0.0f, 95.0f, -0.1f), eLayerType::InteractableObject, this);

		Char_Cheese* cheese = object::Instantiate<Char_Cheese>(eLayerType::Player, this);
		Player->SetChar(cheese);

		UI_Icons* ui0 = object::Instantiate<UI_Icons>(0, eLayerType::UI, this);
		UI_Icons* ui1 = object::Instantiate<UI_Icons>(1, eLayerType::UI, this);

		mFocus = object::Instantiate<UI_FocusBoxes2>(this, eLayerType::UI, this);
		mFocus->AddSelectObj(character);
		mFocus->AddSelectObj(upgrade);
		mFocus->AddSelectObj(cardbook);
		mFocus->AddSelectObj(gate);


		CollisionManager::SetLayer(eLayerType::Player, eLayerType::InteractableObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Tile, true);

		// LobbyScene_MainCamera
		GameObject* LobbyScenecamera = object::Instantiate<GameObject>(cameraPos, eLayerType::Player, this);
		Camera* cameraComp = LobbyScenecamera->AddComp<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		LobbyScenecamera->AddComp<SCRIPT_MainCamera>();
		//renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

		// LobbyScene_UICamera
		GameObject* LobbySceneUIcamera = object::Instantiate<GameObject>(cameraPos, eLayerType::UI, this);
		Camera* UIcameraComp = LobbySceneUIcamera->AddComp<Camera>();
		UIcameraComp->DisableLayerMask();
		UIcameraComp->TurnLayerMask(eLayerType::UI, true);
		LobbySceneUIcamera->AddComp<SCRIPT_UICamera>();
		

	}
	void LobbyScene::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"Stage0_Forest01");
		}

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
		float BgColor[3] = { 0.0f, 0.0f, 0.0f };
		graphics::GetDevice()->SetBgColor(BgColor);

		const std::wstring path = { L"..\\Resources\\Tile\\lobbyscene_tile" };
		TilePalette::AutoLoad(path);


	}
	void LobbyScene::OnExit()
	{
		renderer::cameras.clear();
		//renderer::mainCamera = nullptr;
	}
}