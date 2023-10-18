#pragma once
#include "sgEntity.h"
//#include "sgLayer.h"

namespace sg
{
	class Layer;
	class GameObject;
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

		void AddGameObj(enums::eLayerType type, GameObject* gameObj);
		void DeleteGameObj(enums::eLayerType type, GameObject* gameObj);

		template <typename T>
		std::vector <T*> FindObjectsOfType();

		Layer& GetLayer(enums::eLayerType type) { return mLayers[(UINT)type]; }

		Scene* GetMyScene(Layer* layer);

	protected:
		std::vector<Layer> mLayers;

	private:

	};
}
