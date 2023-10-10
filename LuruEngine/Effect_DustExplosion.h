#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_DustExplosion : public Gobj_Effect
	{
	public:
		Effect_DustExplosion();
		~Effect_DustExplosion();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
