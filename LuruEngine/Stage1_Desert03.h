#pragma once
#include "SCENE_PlayScene2.h"

namespace sg
{
	class Stage1_Desert03 : public PlayScene2
	{
	public:
		Stage1_Desert03();
		~Stage1_Desert03();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
