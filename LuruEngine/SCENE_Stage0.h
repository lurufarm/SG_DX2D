#pragma once
#include "SCENE_PlayScene.h"

namespace sg
{
	class SCENE_Stage0 : public PlayScene
	{
	public:
		SCENE_Stage0();
		~SCENE_Stage0();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

	protected:
		class Interact_Gate* mGate0;
		class Interact_Gate* mGate1;
		class Interact_Gate* mGate2;
	};
}