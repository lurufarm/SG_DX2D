#pragma once
#include "Gobj_Character.h"

namespace sg
{
	class Char_Lucy : public Gobj_Character
	{
	public:
		Char_Lucy();
		~Char_Lucy();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};

}