#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_Icons : public Gobj_UI
	{
	public:
		UI_Icons(int num);
		~UI_Icons();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		int mNum;

	};
}
