#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_UI.h"
#include "UI_FocusBox.h"

namespace sg
{
	class UI_FocusBoxes : public GameObject
	{
	public:
		UI_FocusBoxes(class Scene* myscene);
		~UI_FocusBoxes();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetSelectObj(GameObject* obj);
		void AddSelectObj(GameObject* obj) { mObjs.insert(std::make_pair(obj->GetOrder(), obj)); }
		GameObject* GetSelectObj() { return mObj; }
		

		UI_FocusBox* mBoxes[4];

	private:

		GameObject* mObj;
		std::map<UINT, GameObject*>mObjs;
		Transform* mTr;

		float mAccDeltaTime = 0;
		float mDir = 65.0f;

		class Scene* mMyScene;

	};
}
