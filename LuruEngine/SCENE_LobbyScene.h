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

	private:
		class UI_FocusBoxes2* mFocus;
	};
}
