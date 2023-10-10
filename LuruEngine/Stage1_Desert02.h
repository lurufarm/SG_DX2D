#pragma once
#include "SCENE_PlayScene.h"

namespace sg
{
	class Stage1_Desert02 : public PlayScene
	{
	public:
		Stage1_Desert02();
		~Stage1_Desert02();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
