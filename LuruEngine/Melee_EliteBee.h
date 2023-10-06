#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_EliteBee : public Monster_Melee
	{
	public:
		Melee_EliteBee();
		~Melee_EliteBee();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
