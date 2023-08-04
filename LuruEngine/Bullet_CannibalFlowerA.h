#pragma once
#include "Gobj_Bullet.h"

namespace sg
{
	class Bullet_CannibalFlowerA : public Gobj_Bullet
	{
	public:
		Bullet_CannibalFlowerA();
		~Bullet_CannibalFlowerA();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
