#pragma once
#include "SCENE_PlayScene.h"

namespace sg
{
	class Stage1_Desert01 : public PlayScene
	{
	public:
		Stage1_Desert01();
		~Stage1_Desert01();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void OnEnter();
		void OnExit();

		class Gobj_Sound* GetDesertFDBGM() { return mBGM; }

	private:

		class Gobj_Sound* mBGM;

	};
}
