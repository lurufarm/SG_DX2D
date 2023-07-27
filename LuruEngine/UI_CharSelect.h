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

	private:
	};
}
