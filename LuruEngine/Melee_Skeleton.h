#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Skeleton : public Monster_Melee
	{
	public:
		Melee_Skeleton();
		~Melee_Skeleton();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
