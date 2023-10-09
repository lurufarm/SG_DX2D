#pragma once
#include "Gobj_Monster.h"

namespace sg
{
	class Boss_Centipede : public Gobj_Monster
	{
	public:

		Boss_Centipede();
		~Boss_Centipede();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
