#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_ProjectileDest : public Gobj_Effect
	{
	public:
		Effect_ProjectileDest();
		~Effect_ProjectileDest();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
