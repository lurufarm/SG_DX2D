#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Larva : public Monster_Melee
	{
	public:
		Melee_Larva();
		~Melee_Larva();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
