#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Bomb : public Monster_Melee
	{
	public:
		Melee_Bomb();
		~Melee_Bomb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
