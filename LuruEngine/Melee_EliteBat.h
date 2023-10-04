#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_EliteBat : public Monster_Melee
	{
	public:
		Melee_EliteBat();
		~Melee_EliteBat();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
