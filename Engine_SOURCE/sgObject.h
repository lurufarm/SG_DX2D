#pragma once
#include "sgSceneManager.h"
#include "sgScene.h"
#include "sgLayer.h"
#include "sgGameObject.h"
#include "sgTransform.h"

namespace sg::object
{
#pragma region Create Objects basically in game
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T();
		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;
		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T();
		Transform* tr = Gobj->GetComp<Transform>();
		tr->SetPosition(pos);

		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;
		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rot, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T();
		Transform* tr = Gobj->GetComp<Transform>();
		tr->SetRotation(rot);
		tr->SetPosition(pos);

		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;

		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rot, Vector3 sca, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T();
		Transform* tr = Gobj->GetComp<Transform>();
		tr->SetScale(sca);
		tr->SetRotation(rot);
		tr->SetPosition(pos);

		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;
		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}
#pragma endregion

	static __forceinline void Destroy(GameObject* Gobj)
	{
		Gobj->SetState(GameObject::eState::Dead);
	}

#pragma region Create Objects have parameters in Constructor

	template <typename T>
	static __forceinline T* Instantiate(auto parameter, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T(parameter);
		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;
		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	template <typename T>
	static __forceinline T* Instantiate(auto parameter, Vector3 pos, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T(parameter);
		Transform* tr = Gobj->GetComp<Transform>();
		tr->SetPosition(pos);
		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;

		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	template <typename T>
	static __forceinline T* Instantiate(auto parameter, Vector3 pos, Vector3 rot, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T(parameter);
		Transform* tr = Gobj->GetComp<Transform>();
		tr->SetRotation(rot);
		tr->SetPosition(pos);
		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;

		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	template <typename T>
	static __forceinline T* Instantiate(auto parameter, Vector3 pos, Vector3 rot, Vector3 sca, enums::eLayerType layer, Scene* sname)
	{
		T* Gobj = new T(parameter);
		Transform* tr = Gobj->GetComp<Transform>();
		tr->SetScale(sca);
		tr->SetRotation(rot);
		tr->SetPosition(pos);

		//Scene* scene = SceneManager::GetActiveScene();
		Scene* scene = sname;

		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}
#pragma endregion
}