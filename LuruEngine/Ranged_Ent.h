#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_Ent : public Monster_Ranged
	{
	public:

		Ranged_Ent();
		~Ranged_Ent();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
