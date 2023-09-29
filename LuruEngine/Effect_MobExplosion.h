#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_MobExplosion : public Gobj_Effect
	{
	public:
		Effect_MobExplosion();
		~Effect_MobExplosion();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}