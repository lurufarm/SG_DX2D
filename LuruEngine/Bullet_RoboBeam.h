#pragma once
#include "Gobj_Bullet.h"

namespace sg
{
	class Bullet_RoboBeam : public Gobj_Bullet
	{
	public:
		Bullet_RoboBeam();	
		Bullet_RoboBeam(int num);	
		~Bullet_RoboBeam();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
		
		float CalculatePercent(const float baseValue, const float targetValue)
		{
			return targetValue / baseValue;
		}

	private:
		class Animator* mAni;


	};
}
