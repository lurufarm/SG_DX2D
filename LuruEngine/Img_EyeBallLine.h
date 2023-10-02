#pragma once
#include "Gobj_MobProjectile.h"
#include "Gobj_Img.h"

namespace sg
{
	class Img_EyeBallLine : public Gobj_Img
	{
	public:
		Img_EyeBallLine(Gobj_Monster* owner);
		~Img_EyeBallLine();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		float mTime;
		
		Gobj_Monster* mOwner;
		Vector3 mDir;
		float mAngle;

	};
}

