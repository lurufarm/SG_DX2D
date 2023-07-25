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
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObj(eLayerType type, GameObject* gameObj);
		void DeleteGameObj(eLayerType type, GameObject* gameObj);

		template <typename T>
		std::vector <T*> FindObjectsOfType()
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

		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

		Scene* GetMyScene(Layer* layer)
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

	protected:
		std::vector<Layer> mLayers;

	private:
	};
}
