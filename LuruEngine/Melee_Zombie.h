#pragma once
#include "Monster_Melee.h"

namespace sg
{
	class Melee_Zombie : public Monster_Melee
	{
	public:
		Melee_Zombie();
		~Melee_Zombie();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		float mMSpeed;

	private:
	};
}
