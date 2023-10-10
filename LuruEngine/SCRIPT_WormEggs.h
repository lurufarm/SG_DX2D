#pragma once
#include "SCRIPT_MeleeMob.h"

namespace sg
{
	class SCRIPT_WormEggs : public SCRIPT_MeleeMob
	{
	public:
		void Update() override;
		void Idle() override;
		void Move() override;
		void Attack() override;


	private:
		bool mSpawned;
	};
}
