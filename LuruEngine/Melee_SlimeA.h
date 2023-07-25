#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_SlimeA : public Monster_Melee
	{
	public:
		Melee_SlimeA();
		~Melee_SlimeA();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
