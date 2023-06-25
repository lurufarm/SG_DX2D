#include "sgScene.h"

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
		//for (Layer& layer : mLayers)
		//{
		//	layer.Initialize(); // Å×½ºÆ®2
		//}
	}
	void Scene::Update()
	{
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