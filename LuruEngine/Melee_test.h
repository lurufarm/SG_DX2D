#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_test : public Monster_Melee
	{
	public:
		Melee_test();
		~Melee_test();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
