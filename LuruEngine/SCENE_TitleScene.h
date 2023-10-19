#pragma once
#include "..\Engine_SOURCE\sgScene.h"

namespace sg
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		class Gobj_Sound* GetTItleBGM() { return mBGM; }

	private:
		class Gobj_Sound* mBGM;
	};
}
