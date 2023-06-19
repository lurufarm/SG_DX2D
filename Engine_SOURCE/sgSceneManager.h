#pragma once
#include "sgScene.h"

namespace sg
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* LoadScene(std::wstring name);

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;

	};
}

