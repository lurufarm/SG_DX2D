#pragma once
#include "sgScene.h"

namespace sg
{
	class Gobj_Character;
	class UI_StatusBase;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();
		static void Release();
		
		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(name, scene));
			//mActiveScene = scene;
			scene->Initialize();
			return true;
		}


		static Scene* LoadScene(std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetActiveScene(std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				mActiveScene = iter->second;
		}

		static Scene* LoadNextScene();
		static Scene* GetNextScene();

		static void AddChar(std::wstring key, Gobj_Character* character)
		{
			mAllChars.insert(std::make_pair(key, character));
		}

		static Scene* FindScene(std::wstring scene)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(scene);

			if (iter != mScenes.end())
				return iter->second;

			return nullptr;
		}

		static Gobj_Character* GetChar(std::wstring key)
		{
			std::map<std::wstring, Gobj_Character*>::iterator iter = mAllChars.find(key);
			if (iter != mAllChars.end())
				return iter->second;
			else
				return nullptr;
		}

		static UI_StatusBase* GetStatusBase() { return mStatus; }

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;

		static std::map<std::wstring, Gobj_Character*> mAllChars;
		static UI_StatusBase* mStatus;

	};
}

