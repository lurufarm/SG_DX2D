#include "sgSceneManager.h"
#include "..\LuruEngine\Gobj_Character.h"
#include "..\LuruEngine\Char_Cheese.h"
#include "..\LuruEngine\Char_Lucy.h"

namespace sg
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	std::map<std::wstring, Gobj_Character*> SceneManager::mAllChars = {};

	void SceneManager::Initialize()
	{
		mAllChars.clear();
		Char_Cheese* cheese = new Char_Cheese();
		Char_Lucy* lucy = new Char_Lucy();
		mAllChars.insert(std::make_pair(cheese->GetName(), cheese));
		mAllChars.insert(std::make_pair(lucy->GetName(), lucy));
		//cheese->Initialize();
		//lucy->Initialize();
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
}