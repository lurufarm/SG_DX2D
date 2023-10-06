#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_MummyBomb : public Monster_Ranged
	{
	public:

		Ranged_MummyBomb();
		~Ranged_MummyBomb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
