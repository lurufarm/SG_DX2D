#pragma once
#include "Monster_Melee.h"

	namespace sg
{
	class Melee_Mummy : public Monster_Melee
	{
	public:
		Melee_Mummy();
		~Melee_Mummy();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
