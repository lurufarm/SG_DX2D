#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_RockDust : public Gobj_Effect
	{
	public:
		Effect_RockDust();
		~Effect_RockDust();
		
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
