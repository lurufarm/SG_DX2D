#pragma once
#include "SCENE_PlayScene.h"

namespace sg
{
	class Stage0_Forest02 : public PlayScene
	{
	public:
		Stage0_Forest02();
		~Stage0_Forest02();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
