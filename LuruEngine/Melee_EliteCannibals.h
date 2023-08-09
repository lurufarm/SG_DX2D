#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_EliteCannibals : public Monster_Melee
	{
	public:
		Melee_EliteCannibals();
		~Melee_EliteCannibals();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
