#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class UI_Select : public Gobj_UI
	{
	public:
		UI_Select(bool type);
		~UI_Select();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		bool mType;
		bool mFocused;

	};
}
