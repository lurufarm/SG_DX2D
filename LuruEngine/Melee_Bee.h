#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Bee : public Monster_Melee
	{
	public:
		Melee_Bee();
		~Melee_Bee();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
