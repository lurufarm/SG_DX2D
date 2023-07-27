#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_FirePlate : public Gobj_Effect
	{
	public:
		Effect_FirePlate();
		~Effect_FirePlate();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}