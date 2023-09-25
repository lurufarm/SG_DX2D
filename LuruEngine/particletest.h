#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"

namespace sg
{
	class particletest : public GameObject
	{
	public:
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class ParticleSystem* mPs;
		Transform* mTr;

	};
}