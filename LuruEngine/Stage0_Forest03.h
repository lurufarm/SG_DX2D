#pragma once
#include "SCENE_Stage0.h"

namespace sg
{
	class Stage0_Forest03 : public SCENE_Stage0
	{
	public:
		Stage0_Forest03();
		~Stage0_Forest03();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	};
}
