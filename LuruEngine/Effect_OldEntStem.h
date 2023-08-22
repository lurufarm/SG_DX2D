#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_OldEntStem : public Gobj_Effect
	{
	public:
		Effect_OldEntStem();
		~Effect_OldEntStem();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
