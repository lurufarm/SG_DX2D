#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_Explosion : public Gobj_Effect
	{
	public:
		Effect_Explosion();
		~Effect_Explosion();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}