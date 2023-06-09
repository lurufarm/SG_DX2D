#pragma once
#include "sgEntity.h"
#include "sgGameObject.h"

namespace sg
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<GameObject*> mGameObjects;

		class Nemo* mPlayer;

	};
}
