#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_TextBG : public Gobj_UI
	{
	public:
		UI_TextBG();
		~UI_TextBG();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
	private:

		//Vector2 

	};
}
