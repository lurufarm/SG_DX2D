#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_Character.h"
#include "SCRIPT_CameraScript.h"

namespace sg
{
	class Gobj_Character;
	class Gobj_Player : public GameObject
	{
	public:
		Gobj_Player();
		~Gobj_Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		static void SetChar(Gobj_Character* character)
		{ 
			mpChar = character;
		}
		Gobj_Character* GetChar() { return mpChar; }

		static void SetEnemyNearby(bool value) { mEnemyNearby = value; }
		static bool GetEnemyNearby() { return mEnemyNearby; }

	private:

		class Transform* mTr;
		class MeshRenderer* mMr;
		class Collider2D* mCol;

		static Gobj_Character* mpChar;
		//static Gobj_Character::BasicStat mpStat;
		static std::vector<Gobj_Character*> mCompanies;
		static bool mEnemyNearby;

	};
}
