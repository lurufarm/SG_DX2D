#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_LaserFiring : public Gobj_Effect
	{
	public:
		Effect_LaserFiring();
		~Effect_LaserFiring();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
