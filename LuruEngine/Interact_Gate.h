#pragma once
#include "Gobj_Interactable.h"
#include "..\Engine_SOURCE\sgSceneManager.h"

namespace sg
{
	class Gobj_Item;
	class Interact_Gate : public Gobj_Interactable
	{
	public:
		Interact_Gate(int num);
		~Interact_Gate();
		
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetNextScene(std::wstring scene)
		{
			mNextScene = SceneManager::FindScene(scene);
		}

		void Open() { mOpen = true; }
		bool GetIsOpen() { return mOpen; }

		Gobj_Item* GetItem() { return mItem; }
		void SetItem(Gobj_Item* item) { mItem = item; }

	private:

		int mGateType;
		bool mOpen;
		class Animator* mAni;
		class Scene* mNextScene;
		Gobj_Item* mItem;

	};
}
