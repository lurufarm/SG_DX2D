#pragma once
#include "SCENE_PlayScene2.h"

namespace sg
{
	class Stage1_Desert04 : public PlayScene2
	{
	public:
		Stage1_Desert04();
		~Stage1_Desert04();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
