#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_TextBG_left : public Gobj_Img
	{
	public:
		Img_TextBG_left();
		~Img_TextBG_left();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
