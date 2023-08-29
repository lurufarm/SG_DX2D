#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_LevUP2 : public Gobj_Img
	{
	public:
		Img_LevUP2();
		~Img_LevUP2();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
		class Light* mLg;
	};
}