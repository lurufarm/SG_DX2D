#pragma once
#include "Gobj_Effect.h"

namespace sg
{
	class Effect_ProjectileDest2 : public Gobj_Effect
	{
	public:
		Effect_ProjectileDest2();
		~Effect_ProjectileDest2();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		float mTime;
	};
}
