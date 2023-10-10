#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Scarab : public Monster_Melee
	{
	public:
		Melee_Scarab();
		~Melee_Scarab();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
