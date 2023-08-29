#pragma once
#include "Gobj_Bullet.h"

namespace sg
{
	class Bullet_CheeseArrow : public Gobj_Bullet
	{
	public:
		Bullet_CheeseArrow();
		Bullet_CheeseArrow(int num);
		~Bullet_CheeseArrow();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	

	};
}
