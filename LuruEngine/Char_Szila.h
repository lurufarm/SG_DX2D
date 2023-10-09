#pragma once
#include "Gobj_Character.h"

namespace sg
{
	class Char_Szila : public Gobj_Character
	{
	public:
		Char_Szila();
		~Char_Szila();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
