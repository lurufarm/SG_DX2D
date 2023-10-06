#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_LizardSpear : public Monster_Ranged
	{
	public:

		Ranged_LizardSpear();
		~Ranged_LizardSpear();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
