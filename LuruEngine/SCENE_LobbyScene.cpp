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
#include "..\Engine_SOURCE\sgLayer.h"

#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgParticleSystem.h"

#include "..\Engine_SOURCE\sgAudioListener.h"
#include "..\Engine_SOURCE\sgAudioClip.h"
#include "..\Engine_SOURCE\sgAudioSource.h"



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

#include "Img_LobbyTorch.h"

#include "Gobj_Player.h"
#include "Char_Cheese.h"
#include "Char_Lucy.h"
#include "Char_Robo.h"

#include "Tile_TilePalette.h"

#include "SCRIPT_MainCamera.h"
#include "SCRIPT_UICamera.h"
#include "SCRIPT_BGCamera.h"

#include "Gobj_Sound.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	UI_FocusBoxes2* LobbyScene::mFocus = nullptr;

	LobbyScene::LobbyScene()
	{
		SetName(L"02_LobbyScene");
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		Player = object::MakePlayer();
		Player->Initialize();

		mBGM = object::Instantiate<Gobj_Sound>(eLayerType::BGImg, this);
		mBGM->SetSound(L"BGM_Lobby");

		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		object::Instantiate<Img_Space1>(eLayerType::BGImg, this)->AddComp<SCRIPT_BGCamera>();
		object::Instantiate<Img_Space2>(eLayerType::BGImg, this)->AddComp<SCRIPT_BGCamera>();
		object::Instantiate<Img_LobbyMap>(eLayerType::BGImg, this);
		object::Instantiate<Img_LobbyMolding>(Vector3(-71.5, 55.25, 0.0f), eLayerType::BGImg, this);
		object::Instantiate<Img_LobbyMolding>(Vector3(71.5, 55.25, 0.0f), eLayerType::BGImg, this);
		Img_LobbyTorch* torch0 = object::Instantiate<Img_LobbyTorch>(Vector3(30.f, 50.0f, -0.5f), eLayerType::BGImg, this);
		Img_LobbyTorch* torch1 = object::Instantiate<Img_LobbyTorch>(Vector3(-30.f, 50.0f, -0.5f), eLayerType::BGImg, this);

		Interact_LobbyCharacter* character = object::Instantiate<Interact_LobbyCharacter>(Vector3(-35.75, 6.5f, -0.1f), eLayerType::InteractableObject, this);
		Interact_LobbyUpgrade* upgrade = object::Instantiate<Interact_LobbyUpgrade>(Vector3(35.75, 6.5f, -0.1f), eLayerType::InteractableObject, this);
		Interact_LobbyCardBook* cardbook = object::Instantiate<Interact_LobbyCardBook>(Vector3(35.75, -50.0f, -0.1f), eLayerType::InteractableObject, this);
		Interact_LobbyGate* gate = object::Instantiate<Interact_LobbyGate>(Vector3(0.0f, 95.0f, -0.1f), eLayerType::InteractableObject, this);

		//UI_Icons* ui0 = object::Instantiate<UI_Icons>(0, eLayerType::UI, this);
		//UI_Icons* ui1 = object::Instantiate<UI_Icons>(1, eLayerType::UI, this);

		mFocus = object::Instantiate<UI_FocusBoxes2>(this, eLayerType::UI, this);
		mFocus->AddSelectObj(character);
		mFocus->AddSelectObj(upgrade);
		mFocus->AddSelectObj(cardbook);
		mFocus->AddSelectObj(gate);

		// LobbyScene_MainCamera
		GameObject* LobbyScenecamera = object::Instantiate<GameObject>(cameraPos, eLayerType::Player, this);
		mCamera = LobbyScenecamera->AddComp<Camera>();
		mCamera->TurnLayerMask(eLayerType::UI, false);
		LobbyScenecamera->AddComp<SCRIPT_MainCamera>();
		renderer::mainCamera = mCamera;


		// LobbyScene_UICamera
		GameObject* LobbySceneUIcamera = object::Instantiate<GameObject>(cameraPos, eLayerType::UI, this);
		Camera* UIcameraComp = LobbySceneUIcamera->AddComp<Camera>();
		UIcameraComp->DisableLayerMask();
		UIcameraComp->TurnLayerMask(eLayerType::UI, true);

		LobbySceneUIcamera->AddComp<SCRIPT_UICamera>();


		 //Directional Light
		GameObject* light = new GameObject();
		AddGameObj(eLayerType::Light, light);
		Light* lightcomp = light->AddComp<Light>();
		Vector4 lightcolor = Vector4(0.6f, 0.6f, 0.8f, 1.0f);
		lightcomp->SetType(eLightType::Directional);
		lightcomp->SetColor(lightcolor);

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
		mBGM->Play();
		//renderer::lightsBuffer->Clear();

		const std::wstring path0 = { L"..\\Resources\\Tile\\LobbyScene_00" };
		TilePalette::AutoLoad(path0);
		const std::wstring path1 = { L"..\\Resources\\Tile\\LobbyScene_01" };
		TilePalette::AutoLoad(path1);

		if (renderer::mainCamera != mCamera && renderer::mainCamera != nullptr)
			renderer::mainCamera = mCamera;

		float BgColor[3] = { 0.0f, 0.0f, 0.0f };
		graphics::GetDevice()->SetBgColor(BgColor);
		AddGameObj(eLayerType::Player, Player);
		Player->Initialize2();
	}
	void LobbyScene::OnExit()
	{
		mBGM->Stop();
		DeleteGameObj(eLayerType::Player, Player);
	}


	void LobbyScene::FocusBoxesPaused()
	{
		mFocus->SetState(GameObject::eState::Paused);
	}
	void LobbyScene::FocusBoxesActive()
	{
		mFocus->SetState(GameObject::eState::Active);
	}
}