#pragma once
#include "Gobj_Character.h"

namespace sg
{
	class Char_Robo : public Gobj_Character 
	{
	public:
		Char_Robo();
		~Char_Robo();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
