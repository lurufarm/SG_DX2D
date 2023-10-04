#pragma once
#include "SCENE_PlayScene2.h"

namespace sg
{
	class Stage0_Forest07 : public PlayScene2
	{
	public:
		Stage0_Forest07();
		~Stage0_Forest07();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
