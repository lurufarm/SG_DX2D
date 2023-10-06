#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Snake : public Monster_Melee
	{
	public:
		Melee_Snake();
		~Melee_Snake();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
