#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_Character.h"
#include "SCRIPT_CameraScript.h"

namespace sg
{
	class Gobj_Player : public GameObject
	{
	public:
		Gobj_Player();
		~Gobj_Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		//void SetChar(Gobj_Character* character) 
		//{ 
		//	mChar = character; 
		//}

	private:

		//static Gobj_Character* mChar;
		//static std::vector<Gobj_Character*> mCompanies;
		class Transform* mTr;
		class MeshRenderer* mMr;
		class Collider2D* mCol;

	};
}
