#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_FireLizard : public Monster_Ranged
	{
	public:

		Ranged_FireLizard();
		~Ranged_FireLizard();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
