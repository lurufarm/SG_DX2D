#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Crack : public Gobj_Img
	{
	public:
		Img_Crack();
		~Img_Crack();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void AniNum(int num) { mAniNum = num; }

	private:
		class Animator* mAni;
		//class Light* mLg;
		int mAniNum;

	};
}
