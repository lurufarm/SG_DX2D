#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Space2 : public Gobj_Img
	{
	public:
		Img_Space2();
		~Img_Space2();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
