#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_CannibalFlowerA : public Monster_Ranged
	{
	public:
		Ranged_CannibalFlowerA();
		~Ranged_CannibalFlowerA();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};

}