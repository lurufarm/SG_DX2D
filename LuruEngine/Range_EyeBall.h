#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Range__EyeBall : public Monster_Ranged
	{
	public:
		Range__EyeBall();
		~Range__EyeBall();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};

}