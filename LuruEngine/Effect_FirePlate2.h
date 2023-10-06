#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_FirePlate2 : public Gobj_Effect
	{
	public:
		Effect_FirePlate2();
		~Effect_FirePlate2();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}