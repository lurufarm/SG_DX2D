#pragma once
#include "Monster_Ranged.h"

namespace sg
{
	class Boss_OldEnt : public Monster_Ranged
	{
	public:
		Boss_OldEnt();
		~Boss_OldEnt();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetProjPos(Vector3 pos) { mProjPos = pos; }
		Vector3 GetProjPos() { return mProjPos; }

	private:

		Vector3 mProjPos;

	};

}