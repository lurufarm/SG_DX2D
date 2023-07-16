#pragma once
#include "..\\Engine_SOURCE\sgScene.h"

namespace sg
{
	class SCENE_ToolScene : public Scene
	{
	public:
		SCENE_ToolScene();
		~SCENE_ToolScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
