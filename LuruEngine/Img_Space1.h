#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Space1 : public Gobj_Img
	{
	public:
		Img_Space1();
		~Img_Space1();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
