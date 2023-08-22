#pragma once
#include "sgSceneManager.h"
#include "sgScene.h"
#include "sgLayer.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "..\LuruEngine\Gobj_Player.h"
#include "..\LuruEngine\Gobj_MobProjectile.h"
#include "..\LuruEngine\SCRIPT_MobProjectile.h"
#include "..\LuruEngine\Bullet_SlicedApple.h"
#include "..\LuruEngine\scene_pl"

namespace sg::object
{
#pragma region Create Objects basically in game

	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer)
	{
		T* Gobj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		//Scene* scene = sname;
		scene->AddGameObj(layer, Gobj);

		return Gobj;
	}

	static __forceinline Gobj_Player* MakePlayer()
	{
		Gobj_Player* player = new Gobj_Player();
		Scene* scene = SceneManager::GetActiveScene();
		
		return player;
	}

	static __forceinline Gobj_Monster* MakeMonster(Vector3 pos)
	{
		Gobj_Monster* mob = new Gobj_Monster();
		mob->GetComp<Transform>()->SetPosition(pos);
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObj(eLayerType::Monster, mob);

		return mob;
	}
	static __forceinline Bullet_SlicedApple* SlicedApple(Vector3 pos, int a)
	{
		Bullet_SlicedApple* sa = new Bullet_SlicedApple(pos, a);
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObj(eLayerType::Monster_Bullet2, sa);

		return sa;
	}
	
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