#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_UI.h"
#include "UI_FocusBox.h"

namespace sg
{
	class UI_FocusBoxes2 : public GameObject
	{
	public:
		UI_FocusBoxes2(class Scene* myscene);
		~UI_FocusBoxes2();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetSelectObj(GameObject* obj);
		void AddSelectObj(GameObject* obj)
		{
			mObjs.push_back(obj);
		}
		GameObject* GetSelectObj() 
		{ 
			return mObj; 
		}


		UI_FocusBox* mBoxes[4];

	private:

		GameObject* mObj;
		std::vector<GameObject*>mObjs;
		Transform* mTr;

		float mAccDeltaTime = 0;
		float mDir = 65.0f;

		class Scene* mMyScene;

	};
}
