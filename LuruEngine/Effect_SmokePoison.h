#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_SmokePoison : public Gobj_Effect
	{
	public:
		Effect_SmokePoison();
		~Effect_SmokePoison();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
