#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_LaserHit : public Gobj_Effect
	{
	public:
		Effect_LaserHit();
		~Effect_LaserHit();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
