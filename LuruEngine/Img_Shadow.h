#pragma once
#include "Gobj_Img.h"
#include "Gobj_Monster.h"

namespace sg
{
	class Img_Shadow : public Gobj_Img
	{
	public:
		Img_Shadow();
		~Img_Shadow();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetShadowTarget(GameObject* target) 
		{ 
			mTarget = target;
			/*if (mTarget == dynamic_cast<Gobj_Monster*>(mTarget))
			{
				mSpeed = dynamic_cast<Gobj_Monster*>(mTarget)->GetStat().mSpeed;
			}*/
		}

	private:
		float mSpeed;
		float mTime;
		GameObject* mTarget;
	};
}
