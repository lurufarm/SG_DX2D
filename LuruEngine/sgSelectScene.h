#pragma once
#include "..\Engine_SOURCE\sgScene.h"
#include "UI_FocusBoxes.h"

namespace sg
{
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		~SelectScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	private:
		//std::vector<GameObject*> mSelectObj;
		UI_FocusBoxes* mFocus;
	};
}