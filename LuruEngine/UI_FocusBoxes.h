#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_UI.h"
#include "UI_FocusBox.h"

namespace sg
{
	class UI_FocusBoxes : public GameObject
	{
	public:
		UI_FocusBoxes();
		~UI_FocusBoxes();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetSelectObj(GameObject* obj);
		GameObject* GetSelectObj() { return mObj; }

	private:

		GameObject* mObj;

		UI_FocusBox* mFirst;
		UI_FocusBox* mSecond;
		UI_FocusBox* mThird;
		UI_FocusBox* mFourth;

		Transform* mTr;

	};
}
