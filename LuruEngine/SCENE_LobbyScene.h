#pragma once
#include "..\Engine_SOURCE\sgScene.h"

namespace sg
{
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		virtual ~LobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

		static void FocusBoxesPaused();
		static void FocusBoxesActive();

	private:
		static class UI_FocusBoxes2* mFocus;
		class Gobj_Sound* mBGM;
		class Camera* mCamera;
	};
}
