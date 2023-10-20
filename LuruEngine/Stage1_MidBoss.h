#pragma once
#include "SCENE_PlayScene2.h"

namespace sg
{
	class Stage1_MidBoss : public PlayScene2
	{
	public:
		Stage1_MidBoss();
		~Stage1_MidBoss();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();
	private:
		class Gobj_Sound* mBGM;
	};
}
