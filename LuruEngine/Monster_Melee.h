#pragma once
#include "Gobj_Monster.h"
#include "SCRIPT_MeleeMob.h"

namespace sg
{
	class Monster_Melee : public Gobj_Monster
	{
	public:
		std::wstring& GetName() { return Entity::GetName(); }
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
