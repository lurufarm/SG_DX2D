#include "sgScene.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgLight.h"

namespace sg
{
	Scene::Scene()
		: mTime(0.0f)
	{
		mLayers.resize((int)sg::enums::eLayerType::End);
		Scene::Initialize();
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		light = new GameObject();
		AddGameObj(eLayerType::Light, light);
		light->AddComp<Light>();
	}
	void Scene::Update()
	{
		mTime += Time::DeltaTime();

		for (Layer& layer : mLayers)
		{
			layer.Update(); 
		}
		if (Input::KeyD(eKeyCode::T))
		{
			SceneManager::LoadScene(L"ToolScene");
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
		mLayers[(int)type].AddGameObj(gameObj);
	}
	void Scene::DeleteGameObj(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].DeleteGameObj(gameObj);
	}
}