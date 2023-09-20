#pragma once
#include "Gobj_Monster.h"

namespace sg
{
	class Boss_SkelKnight : public Gobj_Monster
	{
	public:

		Boss_SkelKnight();
		~Boss_SkelKnight();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
