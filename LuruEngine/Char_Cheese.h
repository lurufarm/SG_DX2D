#pragma once
#include "Gobj_Character.h"

namespace sg
{
	class Char_Cheese : public Gobj_Character
	{
	public:
		Char_Cheese();
		~Char_Cheese();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
