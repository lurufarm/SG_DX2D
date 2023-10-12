#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_TextBG_right : public Gobj_Img
	{
	public:
		Img_TextBG_right();
		~Img_TextBG_right();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
