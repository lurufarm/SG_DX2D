#include "sgLayer.h"

namespace sg
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
	void Layer::AddGameObj(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}