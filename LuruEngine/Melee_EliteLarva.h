
#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_EliteLarva : public Monster_Melee
	{
	public:
		Melee_EliteLarva();
		~Melee_EliteLarva();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
