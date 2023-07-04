#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Logo : public Gobj_Img
	{
	public:
		Img_Logo();
		~Img_Logo();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
