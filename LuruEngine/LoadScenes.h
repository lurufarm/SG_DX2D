#pragma once
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "SCENE_TitleScene.h"
#include "SCENE_SelectScene.h"
#include "SCENE_LobbyScene.h"
#include "Stage0_Forest01.h"
#include "SCENE_ToolScene.h"
#include "Gobj_Player.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\LuruEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\LuruEngine.lib")
#endif

	sg::Gobj_Player* Player;

namespace sg
{

	void InitializeScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"00_TitleScene");
		SceneManager::CreateScene<SelectScene>(L"01_SelectScene");
		SceneManager::CreateScene<LobbyScene>(L"02_LobbyScene");
		SceneManager::CreateScene<Stage0_Forest01>(L"03_Stage0_Forest01");
		SceneManager::CreateScene<ToolScene>(L"99_ToolScene");

		SceneManager::SetActiveScene(L"00_TitleScene");


	}
}

