#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Cannibals : public Monster_Melee
	{
	public:
		Melee_Cannibals();
		~Melee_Cannibals();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
