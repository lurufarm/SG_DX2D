#pragma once
#include "SCENE_PlayScene2.h"

namespace sg
{
	class Stage0_BossStage : public PlayScene2
	{
	public:
		Stage0_BossStage();
		~Stage0_BossStage();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
