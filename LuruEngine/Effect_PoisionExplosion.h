#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_PoisionExplosion : public Gobj_Effect
	{
	public:
		Effect_PoisionExplosion();
		~Effect_PoisionExplosion();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
