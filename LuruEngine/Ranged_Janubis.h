#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_Janubis : public Monster_Ranged
	{
	public:

		Ranged_Janubis();
		~Ranged_Janubis();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}