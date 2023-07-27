#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_Hit : public Gobj_Effect
	{
	public:
		Effect_Hit();
		~Effect_Hit();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}