#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_LevUP : public Gobj_Img
	{
	public:
		Img_LevUP();
		~Img_LevUP();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
	private:

		float mTime;

	};
}
