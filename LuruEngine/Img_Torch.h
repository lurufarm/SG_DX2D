#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Torch : public Gobj_Img
	{
	public:
		Img_Torch();
		~Img_Torch();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
		class Light* mLg;

	};
}
