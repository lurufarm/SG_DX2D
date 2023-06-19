#pragma once
#include "sgEntity.h"
#include "sgLayer.h"

namespace sg
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObj(eLayerType type, GameObject* gameObj);

	private:
		std::vector<Layer> mLayers;
	};
}
