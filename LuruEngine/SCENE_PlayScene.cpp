#include "SCENE_PlayScene.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	bool PlayScene::mDay = true;

	PlayScene::PlayScene()
	{
		SetName(L"PlayScene");
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mLight = new GameObject();
		mLg = mLight->AddComp<Light>();
		AddGameObj(eLayerType::Light, mLight);
		mLg->SetType(eLightType::Directional);
		mLg->SetColor(mDayLight);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::KeyD(eKeyCode::B))
		{
			SceneManager::LoadScene(L"LobbyScene");
		}

		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		renderer::mainCamera = mCamera;

		AddGameObj(eLayerType::Player, Player);

	}
	void PlayScene::OnExit()
	{
		DeleteGameObj(eLayerType::Player, Player);
	}
}