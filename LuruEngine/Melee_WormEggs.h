#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_WormEggs : public Monster_Melee
	{
	public:
		Melee_WormEggs();
		~Melee_WormEggs();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
