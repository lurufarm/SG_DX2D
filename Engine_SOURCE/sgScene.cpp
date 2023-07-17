#include "sgScene.h"
#include "sgInput.h"
#include "sgSceneManager.h"

namespace sg
{
	Scene::Scene()
	{
		mLayers.resize((int)sg::enums::eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	
	}
	void Scene::Update()
	{
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
}