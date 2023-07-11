#pragma once
#include "..\Engine_SOURCE\sgScene.h"

namespace sg
{
	class SCENE_PlayScene : public Scene
	{
	public:
		SCENE_PlayScene();
		~SCENE_PlayScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

	protected:
		bool mClear;
	private:
	};
}
