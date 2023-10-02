#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Ranged_EyeBall : public Monster_Ranged
	{
	public:
		Ranged_EyeBall();
		~Ranged_EyeBall();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};

}