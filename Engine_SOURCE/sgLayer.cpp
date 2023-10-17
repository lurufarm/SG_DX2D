#include "sgLayer.h"

namespace sg
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{

		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			delete mGameObjects[i];
			mGameObjects[i] = nullptr;
		}
		//for (GameObject* gameObj : mGameObjects)
		//{
		//	if (gameObj == nullptr)
		//		continue;

		//	delete gameObj;
		//	gameObj = nullptr;

		//}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{

		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
		}
		//for (GameObject* gameObj : mGameObjects)
		//{
		//		gameObj->Update();
		//}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Active)
				gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Active)
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
		gameObj->SetMyLayer(this);
		mGameObjects.push_back(gameObj);
	}
	void Layer::DeleteGameObj(GameObject* gameObj)
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();
		for (; iter != mGameObjects.end(); iter++)
		{
			if (gameObj == *iter)
			{
				gameObj->SetMyLayer(nullptr);
				mGameObjects.erase(iter);
				return;
			}
		}
	}
}