#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_MummyPoison : public Monster_Melee
	{
	public:
		Melee_MummyPoison();
		~Melee_MummyPoison();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
