#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_LizardSword : public Monster_Melee
	{
	public:
		Melee_LizardSword();
		~Melee_LizardSword();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
