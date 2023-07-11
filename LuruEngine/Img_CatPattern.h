#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_CatPattern : public Gobj_Img
	{
	public:
		Img_CatPattern();
		~Img_CatPattern();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
