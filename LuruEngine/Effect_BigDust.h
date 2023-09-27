#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_BigDust : public Gobj_Effect
	{
	public:
		Effect_BigDust();
		~Effect_BigDust();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
