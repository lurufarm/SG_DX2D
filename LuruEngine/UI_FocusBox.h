#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_FocusBox : public Gobj_UI
	{
	public:
		UI_FocusBox(int num);
		~UI_FocusBox();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		int mNum;

	};
}
