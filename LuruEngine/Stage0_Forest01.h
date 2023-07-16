#pragma once
#include "SCENE_Stage0.h"

namespace sg
{
	class Stage0_Forest01 : public SCENE_Stage0
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
	private:

		Camera* mCamera;
	};
}
