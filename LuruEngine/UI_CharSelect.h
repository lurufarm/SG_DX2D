#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_CharSelect : public Gobj_UI
	{
	public:
		UI_CharSelect();
		~UI_CharSelect();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		class UI_CharBox* GetBoxes(int a, int b) { return mBoxes[a][b]; }

	private:

		class UI_CharBox* mBoxes[2][5];
		class UI_FocusBoxes* mFocus;
	};
}
