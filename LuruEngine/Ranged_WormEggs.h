#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_WormEggs : public Monster_Ranged
	{
	public:

		Ranged_WormEggs();
		~Ranged_WormEggs();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		bool mLaunched;

	};
}
