#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_HPBase : public Gobj_UI
	{
	public:
		UI_HPBase();
		~UI_HPBase();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
