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

		void AddGameObj(GameObject* gameObj);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
