#pragma once
#include "Gobj_Monster.h"

namespace sg
{
	class Monster_Ranged : public Gobj_Monster
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
