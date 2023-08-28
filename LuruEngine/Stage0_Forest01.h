#pragma once
#include "SCENE_PlayScene.h"

namespace sg
{
	class Stage0_Forest01 : public PlayScene
	{
	public:
		Stage0_Forest01();
		~Stage0_Forest01();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
