#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Bat : public Monster_Melee
	{
	public:
		Melee_Bat();
		~Melee_Bat();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
