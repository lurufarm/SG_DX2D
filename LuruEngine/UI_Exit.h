#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_Exit : public Gobj_UI
	{
	public:
		UI_Exit();
		~UI_Exit();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}