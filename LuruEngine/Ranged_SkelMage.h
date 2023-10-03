#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_SkelMage : public Monster_Ranged
	{
	public:
		Ranged_SkelMage();
		~Ranged_SkelMage();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	};
}
