#include "sgSceneManager.h"
#include "..\LuruEngine\Gobj_Character.h"
#include "..\LuruEngine\Char_Cheese.h"
#include "..\LuruEngine\Char_Lucy.h"
#include "..\LuruEngine\Char_Robo.h"
#include "..\LuruEngine\Char_Szila.h"
#include "..\LuruEngine\UI_StatusBase.h"

namespace sg
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	std::map<std::wstring, Gobj_Character*> SceneManager::mAllChars = {};
	UI_StatusBase* SceneManager::mStatus = nullptr;

	void SceneManager::Initialize()
	{
		mAllChars.clear();
		Char_Cheese* cheese = new Char_Cheese();
		Char_Lucy* lucy = new Char_Lucy();
		Char_Robo* robo = new Char_Robo();
		Char_Szila* szila = new Char_Szila();
		mAllChars.insert(std::make_pair(cheese->GetName(), cheese));
		mAllChars.insert(std::make_pair(lucy->GetName(), lucy));
		mAllChars.insert(std::make_pair(robo->GetName(), robo));
		mAllChars.insert(std::make_pair(szila->GetName(), szila));
		mStatus = new UI_StatusBase();
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}

	Scene* SceneManager::LoadNextScene()
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(GetActiveScene()->GetName());
		iter++;

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}
	Scene* SceneManager::GetNextScene()
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(GetActiveScene()->GetName());
		iter++;

		if (iter == mScenes.end())
			return nullptr;

		return iter->second;
	}
}