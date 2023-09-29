#pragma once
#include "SCRIPT_MeleeMob.h"

namespace sg
{
	class SCRIPT_MeleeZombie : public SCRIPT_MeleeMob
	{
	public:

		void Move() override;

	private:
		class Melee_Zombie* mOwner2;
	};
}
