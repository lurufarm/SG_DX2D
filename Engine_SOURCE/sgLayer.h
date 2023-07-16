#pragma once
#include "sgGameObject.h"

namespace sg
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		void AddGameObj(GameObject* gameObj);
		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}
		
		Layer* GetMyLayer(GameObject* obj)
		{
			for (GameObject* gobj : mGameObjects)
			{
				if (gobj == obj)
				{
					return this;
				}
			}
			return nullptr;
		}

		std::vector<GameObject*> GetVector() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
