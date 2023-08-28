#pragma once
#include "SCENE_PlayScene.h"

namespace sg
{
	class Stage0_Forest04 : public PlayScene
	{
	public:
		Stage0_Forest04();
		~Stage0_Forest04();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
