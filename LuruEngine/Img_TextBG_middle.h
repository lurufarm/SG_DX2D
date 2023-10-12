#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_TextBG_middle : public Gobj_Img
	{
	public:
		Img_TextBG_middle(float size);
		~Img_TextBG_middle();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
