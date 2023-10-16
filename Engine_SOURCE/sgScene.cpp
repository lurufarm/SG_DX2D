#include "sgScene.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgObject.h"
#include "..\LuruEngine\UI_StatusBase.h"

namespace sg
{
	Scene::Scene()
	{
		mLayers.resize((int)sg::enums::eLayerType::End);
		//mStatus->Initialize();
		Scene::Initialize();
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		if (Input::KeyD(eKeyCode::T))
		{
			SceneManager::LoadScene(L"99_ToolScene");
		}

		for (Layer& layer : mLayers)
		{
			layer.Update(); 
		}

	}
	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{

		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObj(eLayerType type, GameObject* gameObj)
	{
		gameObj->SetMyScene(this);
		mLayers[(int)type].AddGameObj(gameObj);
	}
	void Scene::DeleteGameObj(eLayerType type, GameObject* gameObj)
	{
		gameObj->SetMyScene(nullptr);
		mLayers[(int)type].DeleteGameObj(gameObj);
	}
}