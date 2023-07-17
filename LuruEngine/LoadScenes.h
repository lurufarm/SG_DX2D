#pragma once
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "SCENE_TitleScene.h"
#include "SCENE_SelectScene.h"
#include "SCENE_LobbyScene.h"
#include "Stage0_Forest01.h"
#include "SCENE_ToolScene.h"

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
		SceneManager::CreateScene<Stage0_Forest01>(L"Stage0_Forest01");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		SceneManager::SetActiveScene(L"TitleScene");
	}
}