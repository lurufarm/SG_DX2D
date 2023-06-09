#include "sgLayer.h"

namespace sg
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
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
	void Layer::Destroy()
	{
		std::set<GameObject*> deleteObj = {};
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				deleteObj.insert(gameObj);
			}
		}

		typedef std::vector<GameObject*>::iterator GameObjectIter;
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end() ; )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteObj.find(*(iter));

			if (deleteIter != deleteObj.end())
			{
				iter = mGameObjects.erase(iter);
				continue;
			}
			
			iter++;
		}

		for (GameObject* deadObj : deleteObj)
		{
			delete deadObj;
			deadObj = nullptr;
		}

	}
	void Layer::AddGameObj(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}