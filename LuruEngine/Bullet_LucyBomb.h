#pragma once
#include "Gobj_Bullet.h"

namespace sg
{
	class Bullet_LucyBomb : public Gobj_Bullet
	{
	public:
		Bullet_LucyBomb();
		~Bullet_LucyBomb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		class Animator* mAni;

	};
}
