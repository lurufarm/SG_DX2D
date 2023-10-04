#pragma once
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "SCENE_TitleScene.h"
#include "SCENE_SelectScene.h"
#include "SCENE_LobbyScene.h"
#include "Stage0_Forest01.h"
#include "Stage0_Forest02.h"
#include "Stage0_Forest03.h"
#include "Stage0_Forest04.h"
#include "Stage0_Forest05.h"
#include "Stage0_Forest06.h"
#include "Stage0_Forest07.h"
#include "Stage0_Forest08.h"
#include "Stage0_BossStage.h"
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
		SceneManager::CreateScene<Stage0_Forest02>(L"04_Stage0_Forest02");
		SceneManager::CreateScene<Stage0_Forest03>(L"05_Stage0_Forest03");
		SceneManager::CreateScene<Stage0_Forest04>(L"06_Stage0_Forest04");
		SceneManager::CreateScene<Stage0_Forest05>(L"07_Stage0_Forest05");
		SceneManager::CreateScene<Stage0_Forest06>(L"08_Stage0_Forest06");
		SceneManager::CreateScene<Stage0_Forest07>(L"09_Stage0_Forest07");
		SceneManager::CreateScene<Stage0_Forest08>(L"10_Stage0_Forest08"); 
		SceneManager::CreateScene<Stage0_BossStage>(L"11_Stage0_BossStage"); 
		SceneManager::CreateScene<ToolScene>(L"99_ToolScene");

		SceneManager::SetActiveScene(L"00_TitleScene");


	}
}

