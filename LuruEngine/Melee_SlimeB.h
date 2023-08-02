#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_SlimeB : public Monster_Melee
	{
	public:
		Melee_SlimeB();
		~Melee_SlimeB();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
