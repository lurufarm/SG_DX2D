#pragma once
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "SCENE_TitleScene.h"
#include "SCENE_SelectScene.h"
#include "SCENE_LobbyScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\LuruEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\LuruEngine.lib")
#endif

namespace sg
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<SelectScene>(L"SelectScene");
		SceneManager::CreateScene<LobbyScene>(L"LobbyScene");
		SceneManager::SetActiveScene(L"TitleScene");
	}
}