#pragma once
#include "SCENE_Stage0.h"

namespace sg
{
	class Stage0_Forest02 : public SCENE_Stage0
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
