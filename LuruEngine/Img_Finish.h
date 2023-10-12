#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Finish : public Gobj_Img
	{
	public:
		Img_Finish();
		~Img_Finish();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		float mSpeed;
		float mTime;
		GameObject* mTarget;
	};
}
