#include "sgScene.h"
#include "sgTime.h"
#include "sgInput.h"
#include "sgSceneManager.h"
#include "sgObject.h"
#include "sgLayer.h"

namespace sg
{
	Scene::Scene()
	{
		mLayers.resize((int)sg::enums::eLayerType::End);
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
	template<typename T>
	inline std::vector<T*> Scene::FindObjectsOfType()
	{
		std::vector<T*> findObjs = {};
		for (Layer* layer : mLayers)
		{
			auto gameObjs = layer->GetGameObjects();
			for (GameObject* obj : gameObjs)
			{
				T* buff = dynamic_cast<T*>(obj);
				if (buff != nullptr)
					findObjs.push_back(buff);
			}
		}

		return findObjs;
	}
	Scene* Scene::GetMyScene(Layer* layer)
	{
		for (Layer& lay : mLayers)
		{
			if (&lay == layer)
			{
				return this;
			}
		}
		return nullptr;
	}
}